//Quick MD3 Fixer
//Fixes MD3's exported from Misfit Model 3D in a jiffy!
//MD3's should be ready to be used after that.

#include <stdio.h>
#include <string>
#include "md3fix.h"

using namespace std;

void main(int argc, char* argv[])
{
	md3_t header;
	md3Surface_t surface;
	string input;
	FILE* fp;

	if (argc == 2)
	{
		input = argv[1];
	}
	else
	{
		printf("Usage: quickmd3 file.md3\n");
		exit(0);
	}
	fp = fopen(input.c_str(), "r+b");
	fread(&header, sizeof(md3_t), 1, fp);
	fseek(fp, header.ofsSurfaces, SEEK_SET);
	for (int i = 0; i < header.numSurfaces; i++)
	{
		md3Shader_t shader;
		md3Triangle_t* mesh;
		int startpos = ftell(fp);
		fread(&surface, sizeof(md3Surface_t), 1, fp);
		fseek(fp, surface.ofsTriangles + startpos, SEEK_SET);
		mesh = new md3Triangle_t[surface.numTriangles];
		fread(mesh, sizeof(md3Triangle_t), surface.numTriangles, fp);
		fseek(fp, surface.ofsShaders + startpos, SEEK_SET);
		fread(&shader, sizeof(md3Shader_t), 1, fp);
		surface.ofsShaders = 108;
		surface.ofsTriangles = 176;
		fseek(fp, startpos, SEEK_SET);
		fwrite(&surface, sizeof(md3Surface_t), 1, fp);
		fseek(fp, startpos + surface.ofsShaders, SEEK_SET);
		fwrite(&shader, sizeof(md3Shader_t), 1, fp);
		fseek(fp, startpos + surface.ofsTriangles, SEEK_SET);
		fwrite(mesh, sizeof(md3Triangle_t), surface.numTriangles, fp);
		delete [] mesh;
		fseek(fp, startpos + surface.ofsEnd, SEEK_SET);
	}
}