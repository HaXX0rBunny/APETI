#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int Load_Level_From_File(char* fileName);
int Save_Level_To_File(char* fileName);

void Save_Integer_To_File(int* pI, FILE* outFile);
void Save_Float_To_File(float* pF, FILE* outFile);
void Save_Vector_To_File(CP_Vector* pVec, FILE* outFile);
void Save_Color_To_File(CP_Color* pColor, FILE* outFile);

void Load_Integer_From_File(int* pI, FILE* inFile);
void Load_Float_From_File(float* pF, FILE* inFile);
void Load_Vector_From_File(CP_Vector* pVec, FILE* inFile);
void Load_Color_From_File(CP_Color* pColor, FILE* inFile);

void Save_Platform(struct Platform* obj, FILE* outFile);
void Load_Platform(struct Platform* obj, FILE* inFile);