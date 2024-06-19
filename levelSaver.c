#include "levelSaver.h"

#define MYLEVEL "myLevel.lvl"

extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];
extern int platformCount;

enum
{
	BUFFERSIZE = 512
};

int Load_Level_From_File(char* fileName)
{
	FILE* inFile = fopen(fileName, "r");

	if (inFile == NULL)
		return 0;

	char str[BUFFERSIZE] = { '\0' };

	int n = 0;
	Load_Integer_From_File(&n, inFile);

	int i = 0;
	for (i = 0; i < n; i++)
	{
		fgets(str, BUFFERSIZE, inFile);

		if (str[0] != '-')
		{
			i--;
			continue;
		}

		struct Platform* platform = Get_First_Hidden_Platform();

		Load_Platform(platform, inFile);
	}

	fclose(inFile);

	return 1;
}

int Save_Level_To_File(char* fileName)
{
	FILE* outFile = fopen(fileName, "w");

	if (outFile == NULL)
		return 0;

	fprintf(outFile, "%d \n", platformCount);

	for (int i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		struct Platform platform = platformList[i];

		if (!platform.exist) continue;

		Save_Platform(&platform, outFile);
	}

	fclose(outFile);
	return 1;
}

void Save_Integer_To_File(int* pI, FILE* outFile)
{
	fprintf(outFile, "%d \n", *pI);
}

void Save_Float_To_File(float* pF, FILE* outFile)
{
	fprintf(outFile, "%f \n", *pF);
}

void Save_Vector_To_File(CP_Vector* pVec, FILE* outFile)
{
	fprintf(outFile, "%f %f \n", pVec->x, pVec->y);
}

void Save_Color_To_File(CP_Color* pColor, FILE* outFile)
{
	fprintf(outFile, "%d %d %d %d \n", pColor->r, pColor->g, pColor->b, pColor->a);
}

void Load_Integer_From_File(int* pI, FILE* inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, inFile);
	sscanf_s(str, "%d", pI);
}

void Load_Float_From_File(float* pF, FILE* inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, inFile);
	sscanf_s(str, "%f", pF);
}

void Load_Vector_From_File(CP_Vector* pVec, FILE* inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, inFile);
	sscanf_s(str, "%f %f", &pVec->x, &pVec->y);
}

void Load_Color_From_File(CP_Color* pColor, FILE* inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, inFile);

	int color[4] = { 0 };

	sscanf_s(str, "%d %d %d %d", &color[0], &color[1], &color[2], &color[3]);

	for (int i = 0; i < 4; i++)
		pColor->rgba[i] = (char)color[i];
}

void Save_Platform(struct Platform* platform, FILE* outFile)
{
	fprintf(outFile, "-\n");

	Save_Vector_To_File(&platform->Pos, outFile);

	Save_Float_To_File(&platform->w, outFile);
	Save_Float_To_File(&platform->h, outFile);

	Save_Integer_To_File(&platform->removability, outFile);

	Save_Color_To_File(&platform->color, outFile);
}

void Load_Platform(struct Platform* platform, FILE* inFile)
{
	Load_Vector_From_File(&platform->Pos, inFile);

	Load_Float_From_File(&platform->w, inFile);
	Load_Float_From_File(&platform->h, inFile);

	Load_Integer_From_File(&platform->removability, inFile);

	Load_Color_From_File(&platform->color, inFile);

	platform->exist = 1;
	platformCount++;
}