//
// Created by MI on 18.01.2021.
//

#include "T2F.h"
#include <assert.h>
#include <math.h>
//-----------------------------------CONST MATRIX--------------------------------------

const BYTE MDS[4][4] = {
        {0x01, 0xEF, 0x5B, 0x5B},
        {0x5B, 0xEF, 0xEF, 0x01},
        {0xEF, 0x5B, 0x01, 0xEF},
        {0xEF, 0x01, 0xEF, 0x5B}
};
const BYTE qt[2][4][16] = {
        //permutation table for q0 operation
        {
                { 0x8, 0x1, 0x7, 0xD, 0x6, 0xF, 0x3, 0x2, 0x0, 0xB, 0x5, 0x9, 0xE, 0xC, 0xA, 0x4 },
                { 0xE, 0xC, 0xB, 0x8, 0x1, 0x2, 0x3, 0x5, 0xF, 0x4, 0xA, 0x6, 0x7, 0x0, 0x9, 0xD },
                { 0xB, 0xA, 0x5, 0xE, 0x6, 0xD, 0x9, 0x0, 0xC, 0x8, 0xF, 0x3, 0x2, 0x4, 0x7, 0x1 },
                { 0xD, 0x7, 0xF, 0x4, 0x1, 0x2, 0x6, 0xE, 0x9, 0xB, 0x3, 0x0, 0x8, 0x5, 0xC, 0xA }
        },

        //permutation table for q1 operation
        {
                { 0x2, 0x8, 0xB, 0xD, 0xF, 0x7, 0x6, 0xE, 0x3, 0x1, 0x9, 0x4, 0x0, 0xA, 0xC, 0x5 },
                { 0x1, 0xE, 0x2, 0xB, 0x4, 0xC, 0x3, 0x7, 0x6, 0xD, 0xA, 0x5, 0xF, 0x9, 0x0, 0x8 },
                { 0x4, 0xC, 0x7, 0x5, 0x1, 0x6, 0x9, 0xA, 0x0, 0xE, 0xD, 0x8, 0x2, 0xB, 0x3, 0xF },
                { 0xB, 0x9, 0x5, 0x1, 0xC, 0x3, 0xD, 0xE, 0x6, 0x4, 0x7, 0xF, 0x2, 0x0, 0x8, 0xA }
        },
};
const BYTE RSMatrix[4][8] = {
        {0x01, 0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E},
        {0xA4, 0x56, 0x82, 0xF3, 0x1E, 0xC6, 0x68, 0xE5},
        {0x02, 0xA1, 0xFC, 0xC1, 0x47, 0xAE, 0x3D, 0x19},
        {0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E, 0x03},
};
//------------------------------------MUTA-FUNCTIONS-----------------------------------
// 32 bit
BYTE b0(UINT x){
    return x & 0xFF;
}
BYTE b1(UINT x){
    return  (x >> 8) & 0xFF;
}
BYTE  b2(UINT x){
    return  (x >> 16) & 0xFF;
}
BYTE  b3(UINT x){
    return  (x >> 24) & 0xFF;
}
UINT BYTES_TO_UINT(BYTE x0, BYTE x1, BYTE x2, BYTE x3){
    return ((x0 << 24) ^ (x1 << 16) ^ (x2 << 8) ^ x3);
}
UINT BYTEARRAY_TO_UINT(const BYTE *x){
    return ((x[0] << 24) ^ (x[1] << 16) ^ (x[2] << 8) ^ x[3]);
}


//-------------------------------------POLYNOMIAL OPERATIONS------------------------
UINT polyMul(UINT A, UINT B){
    UINT t=0;
    while (A)
    {
        if (A&1) t^=B;
        B <<= 1;
        A >>= 1;
    }
    return t;
}

UINT gfMOD(UINT A, UINT modulus){
    UINT tt;

    modulus <<= 7;
    for (int i = 0; i < 8; i++)
    {
        tt = A ^ modulus;
        if (tt < A) A = tt;
        modulus >>= 1;
    }
    return A;
}

#define     gfMul(a, b, modulus)    gfMOD(polyMul(a, b), modulus)
//---------------------------------ALGORYTHMS FUNCS-----------------

//---------------------------------G-BLOCK---------------------------
BYTE q(BYTE x, int op){
    assert((op == 0) || (op == 1));
    //splitting byte into two nibbles
    BYTE a0 = x >> 4;
    BYTE b0 = x & 0x0F;

    BYTE a1 = a0 ^ b0;
    BYTE b1 = a0 ^ ROR4(b0) ^ ((8 * a0) & 0x0F); //ROR4

    BYTE a2 = qt[op][0][a1];
    BYTE b2 = qt[op][1][b1];

    BYTE a3 = a2 ^ b2;
    BYTE b3 = a2 ^ ROR4(b2) ^ ((8 * a2) & 0x0F);  //ROR4
    BYTE a4 = qt[op][2][a3];
    BYTE b4 = qt[op][3][b3];

    return ((b4 << 4) + a4);
}

UINT g(UINT X, UINT S[2]){
    BYTE x0, x1, x2, x3;
    x0 = b0(X);
    x1 = b1(X);
    x2 = b2(X);
    x3 = b3(X);

    x0 = q(q(q(x0,0)^b0(S[0]), 0)^b0(S[1]), 1);
    x1 = q(q(q(x1,1)^b1(S[0]), 0)^b1(S[1]), 0);
    x2 = q(q(q(x2,0)^b2(S[0]), 1)^b2(S[1]), 1);
    x3 = q(q(q(x3,1)^b3(S[0]), 1)^b3(S[1]), 0);

    BYTE x[4] = {x1, x2, x3, x0};

    BYTE t;
    BYTE result[4];

    for (int j = 0; j < 4; j++)
    {
        t = 0;
        for (int k = 0; k < 4; k++)
        {
            t ^= gfMul(MDS[j][k], x[k], 0x169);
        }
        result[3-j] = t;
    }
    return BYTEARRAY_TO_UINT(result);
}
//----------------------------------END OF G-BLOCK--------------------
//----------------------------------- ROUND --------------------------
void ROUNDENCRYPT(UINT R[4], int round, keyS keys){
    UINT T0, T1;
    T0 = g(R[0], keys.Skey);
    T1 = g(ROL(R[1], 8), keys.Skey);

    R[2] = R[0];
    R[3] = R[1];
    //adding keys from keyShedule
    R[0] = ROR(R[2] ^ (T1 + T0 + keys.Kkey[2*round + 8]), 1);
    R[1] = ROL(R[3], 1) ^ (2*T1 + T0 + keys.Kkey[2*round + 9]);

}

void ROUNDDECRYPT(UINT R[4], int round, keyS keys){
    UINT T0, T1;
    T0 = g(R[0], keys.Skey);
    T1 = g(ROL(R[1], 8), keys.Skey);

    R[2] = R[0];
    R[3] = R[1];
    //adding keys from keyShedule
    R[0] = ROL(R[2], 1) ^ (T1 + T0 + keys.Kkey[2*round + 8]);
    R[1] = ROR(R[3] ^ (2*T1 + T0 + keys.Kkey[2*round + 9]), 1);
}

//plain - origin massive
// R - buff with chipher
void encryption(const UINT plain[4], keyS keys, UINT R[4]){
    R[0] = plain[0]^keys.Kkey[0];
    R[1] = plain[1]^keys.Kkey[1];
    R[2] = plain[2]^keys.Kkey[2];
    R[3] = plain[3]^keys.Kkey[3];

    for(int i=0; i<16; i++){
        ROUNDENCRYPT(R, i, keys);
    }

    R[0] = R[0]^keys.Kkey[4];
    R[1] = R[1]^keys.Kkey[5];
    R[2] = R[2]^keys.Kkey[6];
    R[3] = R[3]^keys.Kkey[7];
}


//chipher - origin massive
// R - buff with decrypt
void decryption(const UINT chipher[4], keyS keys, UINT R[4]){
    R[0] = chipher[0]^keys.Kkey[4];
    R[1] = chipher[1]^keys.Kkey[5];
    R[2] = chipher[2]^keys.Kkey[6];
    R[3] = chipher[3]^keys.Kkey[7];

    for(int i=15; i>=0; i--){
        ROUNDDECRYPT(R, i, keys);
    }

    R[0] = R[0]^keys.Kkey[0];
    R[1] = R[1]^keys.Kkey[1];
    R[2] = R[2]^keys.Kkey[2];
    R[3] = R[3]^keys.Kkey[3];
}



//--------------------------------------MATRIX------------------------
UINT RSM(BYTE sd[8])
{
    int j, k;
    BYTE t;
    BYTE result[4];

    for (j = 0; j < 4; j++)
    {
        t = 0;
        for (k = 0; k < 8; k++)
        {
            t ^= gfMul(RSMatrix[j][k], sd[k], 0x14D);
        }
        result[3-j] = t;
    }
    return BYTEARRAY_TO_UINT(result);
}

//----------------------------KEY GENERATION-----------------------------------------
void pushSkeys(const BYTE globalkey[16], keyS key){
    BYTE m07[8] = {globalkey[0], globalkey[1], globalkey[2], globalkey[3],
                   globalkey[4], globalkey[5], globalkey[6], globalkey[7]};
    BYTE m816[8] = {globalkey[8], globalkey[9], globalkey[10], globalkey[11],
                    globalkey[12], globalkey[13], globalkey[14], globalkey[15]};
    UINT S0 = RSM(m07);
    UINT S1 = RSM(m816);

    for(int i = 0; i < 2; i++){
        key.Skey[i] = (i==0) ? S0 : S1;
    }
}

void pushKkeys(const BYTE M[16], keyS key){

    UINT Me[2] = {BYTES_TO_UINT(M[8], M[9], M[10], M[11]),
                  BYTES_TO_UINT(M[0], M[1], M[2], M[3])};
    UINT Mo[2] = {BYTES_TO_UINT(M[12], M[13], M[14], M[15]),
                  BYTES_TO_UINT(M[4], M[5], M[6], M[7])};
//H
    for(int i=0; i < 20; i++){
        UINT K2i, K2i1;
        K2i = g(2*i*RHO, Me);
        K2i1 = ROL(g(2*i*RHO + RHO, Mo), 8);
        key.Kkey[2*i] = K2i + K2i1;
        key.Kkey[2*i + 1] = ROL(K2i + 2*K2i1, 9);
    }
}

void keyShedule(const BYTE M[16], keyS key){
    pushSkeys(&M[16], key);
    pushKkeys(&M[16], key);
}


//---------------------------------------SHIFTS---------------------------------------

//Right circular shift for 4 least significant bits
BYTE ROR4(BYTE x){
    return (((x << 3) & 0xF) | ( (x & 0xF) >> 1));
}
/*
//Left circular shift for unsigned int
UINT ROL(UINT x, BYTE shift){
    BYTE shl = shift % (sizeof(x)*8);
    if (shl == 0) return x;
    return ((x << shl) | (x >> (sizeof(x)*8 - shl)));
}

//Right circular shift for unsigned int
UINT ROR(UINT x, BYTE shift) {
    BYTE shl = shift % (sizeof(x) * 8);
    if (shl == 0) return x;
    return ((x >> shl) | (x << (sizeof(x) * 8 - shl)));
}
 */