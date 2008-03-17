//quickmap - Fixes map files that QuArK exports in Classic Quake texture format so that they
//work in GtkRadiant.

//Basically checks the brush plane definitions at the texture alignment area to make sure there
//eight numbers. If there are not, it is expected that there are only five numbers, so three
//zeroes will be added to the end of the line. Technically, only the spaces are checked after
//the definitions of the three points defining the plane, beginning with the first space before
//the texture name and ending at the newline, and it is expected that there is no trailing whitespace.

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void main(int argc, char* argv[])
{
	FILE* fp;
	unsigned srcfilelength;
	unsigned destsrcfilelength;
	char *srcbuff;
	char *destbuff;

	if (argc < 2)
	{
		cout << "Ussage: quickmap input.map [output.map]\n";
		return;
	}

	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	srcfilelength = ftell(fp);
	srcbuff = new char[srcfilelength];
	fseek(fp, 0, SEEK_SET);
	fread(srcbuff, 1, srcfilelength, fp);
	fclose(fp);

	//Parse the data to find addresses to insert the three zero sequence
	int i = 0;
	int nestlevel = 0;
	int planepointnum = 0; //which brush plane point we are currently at
	bool bBrushPlanePoint = false; //inside the scope of one of the three points defining a brush plane
	//bool bComment = false;
	vector<int> insertaddresses;
	while (i < srcfilelength)
	{
		switch (srcbuff[i])
		{
		/*case '/': ignore comment recognition
			i++;
			if (srcbuff[i] == '/')
			{
				i++;
				bComment = true;
			}
			break;*/

		case '{':
			i++;
			nestlevel++;
			break;

		case '}':
			i++;
			nestlevel--;
			break;

		case '(':
			i++;
			if (nestlevel == 2)
				bBrushPlanePoint = true;
			break;

		case ')':
			i++;
			if (bBrushPlanePoint == true)
			{
				bBrushPlanePoint = false;
				planepointnum++;
			}
			break;

		default:
			/*if (bComment) ignore comment recognition
			{
				if (srcbuff[i] == '\n')
				{
					i++;
					bComment = false;
				}
				else
					i++;
			}
			else */if (planepointnum == 3)
			{
				planepointnum = 0;
				int j = 0;
				while (srcbuff[i] != '\r' && srcbuff[i] != '\n')
				{
					i++;
					if (srcbuff[i] == ' ')
						j++;
				}
				if (j < 8)
					//we're at an insertion address
					insertaddresses.push_back(i);
			}
			else
				i++;
			break;
		}
	}
	destsrcfilelength = srcfilelength + insertaddresses.size() * 6;

	//Copy the data inserting the sequence at designated areas
	destbuff = new char[destsrcfilelength];
	i = 0;
	int j = 0;
	int k = 0;
	while (i < srcfilelength)
	{
		if (insertaddresses[k] == i)
		{
			destbuff[j] = ' '; j++;
			destbuff[j] = '0'; j++;
			destbuff[j] = ' '; j++;
			destbuff[j] = '0'; j++;
			destbuff[j] = ' '; j++;
			destbuff[j] = '0'; j++;
			//insertaddresses.pop();
			k++;
		}
		else
		{
			destbuff[j] = srcbuff[i];
			i++;
			j++;
		}
	}

	//Write the data to the output file
	if (argc == 3)
		fp = fopen(argv[2], "wb");
	else
		fp = fopen(argv[1], "wb");
	fwrite(destbuff, 1, destsrcfilelength, fp);
	fclose(fp);

	//shutdown
	delete []srcbuff;
	delete []destbuff;
}