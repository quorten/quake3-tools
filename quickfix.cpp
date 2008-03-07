//quickfix - fast search & replacer, (very limited)

#include <vector>
#include <cstdio>

using namespace std;

void main()
{
	FILE* fp;
	char* srcbuff;
	char* destbuff;
	unsigned filelength;
	unsigned destfilelength;
	vector<int> insertaddresses;

	fp = fopen("input.map", "rb");
	fseek(fp, 0, SEEK_END);
	filelength = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	srcbuff = new char[filelength];
	fread(srcbuff, 1, filelength, fp);
	fclose(fp);

	int i = 0;
	while (i < filelength)
	{
		if (srcbuff[i] == ' ')
		{
			i++;
			if (srcbuff[i] == '0')
			{
				i++;
				if (srcbuff[i] == '.')
				{
					i++;
					if (srcbuff[i] == '5')
					{
						i++;
						if (srcbuff[i] == ' ')
						{
							insertaddresses.push_back(i - 1);
						}
					}
				}
			}
		}
		else
			i++;
	}
	destfilelength = filelength + insertaddresses.size();

	destbuff = new char[destfilelength];

	i = 0;
	int j = 0;
	int k = 0;
	while (i < filelength)
	{
		if (insertaddresses[k] == i)
		{
			destbuff[j] = '2'; j++;
			destbuff[j] = '5'; j++;
			i++;
			k++;
		}
		else
		{
			destbuff[j] = srcbuff[i];
			i++;
			j++;
		}
	}
	
	fopen("output.map", "wb");
	fwrite(destbuff, 1, destfilelength, fp);
	fclose(fp);

	delete []srcbuff;
	delete []destbuff;
}