//
// Created by MI on 16.01.2021.
//

#ifndef TFISHC_TF_H
#define TFISHC_TF_H




#include <assert.h>
#include <limits.h>
#include <stdio.h>


#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

typedef struct{
        UINT keys[40];
        short k;
        UINT *SBox;
} TF;

BYTE* encrypt(TF coder, BYTE *plain);
BYTE* decrypt(TF coder, BYTE *cypher);
void printSubkeys();

//System methods
void keySchedule(TF coder, BYTE *key, size_t length);
unsigned long long h(UINT inputWord, const UINT* inputWordArray, short arraySize);
BYTE q(BYTE x, int qt);
BYTE ROR4(BYTE x);
UINT ROR(UINT x, BYTE shift);
UINT ROL(UINT x, BYTE shift);

#endif //TFISHC_TF_H
