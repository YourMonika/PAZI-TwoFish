
//
// Created by MI on 16.01.2021.
//

#include "TF.h"
#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

/********************************Constructor*********************************/
/*TwoFish::TwoFish(BYTE *key, size_t length){
keySchedule(key, length);
}
*/

/*********************************Interface**********************************/
BYTE* encrypt(TF coder, BYTE *plain){

    UINT

            A = (plain[0] << 24) + (plain[1] << 16) + (plain[2] << 8) + plain[3],
            B = (plain[4] << 24) + (plain[5] << 16) + (plain[6] << 8) + plain[7],
            C = (plain[8] << 24) + (plain[9] << 16) + (plain[10] << 8) + plain[11],
            D;
    D = (plain[12] << 24) + (plain[13] << 16) + (plain[14] << 8) + plain[15];

    //whitening
    A ^= coder.keys[0];
    B ^= coder.keys[1];
    C ^= coder.keys[2];
    D ^= coder.keys[3];

    //sixteen roudns
    for(int i = 0; i < 16; i++){
        unsigned long long tA = h(A, coder.SBox, coder.k);
        unsigned long long tB = h(ROL(B, 8), coder.SBox, coder.k); // ROL

        D = ROL(D, 1); //ROL
        C ^= ((tA + tB + coder.keys[2 * i + 8]) & 0xFFFFFFFF);
        D ^= ((tA + 2*tB + coder.keys[2 * i + 9]) & 0xFFFFFFFF);
        C = ROR(C, 1); //ROR

        //swap until last round
        if (i != 15) {
            UINT tmp = C;
            C = A;
            A = tmp;
            tmp = D;
            D = B;
            B = tmp;
        }
    }

    //whitening
    A ^= coder.keys[4];
    B ^= coder.keys[5];
    C ^= coder.keys[6];
    D ^= coder.keys[7];

    plain[0] = (A >> 24) & 0xFF;
    plain[1] = (A >> 16) & 0xFF;
    plain[2] = (A >> 8) & 0xFF;
    plain[3] = A & 0xFF;
    plain[4] = (B >> 24) & 0xFF;
    plain[5] = (B >> 16) & 0xFF;
    plain[6] = (B >> 8) & 0xFF;
    plain[7] = B & 0xFF;
    plain[8] = (C >> 24) & 0xFF;
    plain[9] = (C >> 16) & 0xFF;
    plain[10] = (C >> 8) & 0xFF;
    plain[11] = C & 0xFF;
    plain[12] = (D >> 24) & 0xFF;
    plain[13] = (D >> 16) & 0xFF;
    plain[14] = (D >> 8) & 0xFF;
    plain[15] = D & 0xFF;
    return plain;
}

BYTE* decrypt(TF coder, BYTE *cipher){

    UINT
            A = (cipher[0] << 24) + (cipher[1] << 16) + (cipher[2] << 8) + cipher[3],
            B = (cipher[4] << 24) + (cipher[5] << 16) + (cipher[6] << 8) + cipher[7],
            C = (cipher[8] << 24) + (cipher[9] << 16) + (cipher[10] << 8) + cipher[11],
            D = (cipher[12] << 24) + (cipher[13] << 16) + (cipher[14] << 8) + cipher[15];

    //whitening
    A ^= coder.keys[4];
    B ^= coder.keys[5];
    C ^= coder.keys[6];
    D ^= coder.keys[7];

    //sixteen rounds
    for(int i = 16 - 1; i >= 0; i--){
        unsigned long long tA = h(A, coder.SBox, coder.k);
        unsigned long long tB = h(ROL(B,8), coder.SBox, coder.k); //ROL
        C = ROL(C, 1); //ROL
        C ^= ((tA + tB + coder.keys[2 * i + 8]) & 0xFFFFFFFF);
        D ^= ((tA + 2*tB + coder.keys[2 * i + 9]) & 0xFFFFFFFF);
        D = ROR(D, 1); //ROR

        //swap until last round
        if (i > 0) {
            UINT tmp = C;
            C = A;
            A = tmp;
            tmp = D;
            D = B;
            B = tmp;
        }
    }

    //whitening
    A ^= coder.keys[0];
    B ^= coder.keys[1];
    C ^= coder.keys[2];
    D ^= coder.keys[3];

    cipher[0] = (A >> 24) & 0xFF;
    cipher[1] = (A >> 16) & 0xFF;
    cipher[2] = (A >> 8) & 0xFF;
    cipher[3] = A & 0xFF;
    cipher[4] = (B >> 24) & 0xFF;
    cipher[5] = (B >> 16) & 0xFF;
    cipher[6] = (B >> 8) & 0xFF;
    cipher[7] = B & 0xFF;
    cipher[8] = (C >> 24) & 0xFF;
    cipher[9] = (C >> 16) & 0xFF;
    cipher[10] = (C >> 8) & 0xFF;
    cipher[11] = C & 0xFF;
    cipher[12] = (D >> 24) & 0xFF;
    cipher[13] = (D >> 16) & 0xFF;
    cipher[14] = (D >> 8) & 0xFF;
    cipher[15] = D & 0xFF;
    return cipher;
}

void printSubkeys(TF coder){
    for(int i=0; i< 40; i++){
        printf("%u", coder.keys[i]);
    }
}
/*******************************System methods*******************************/
void keySchedule(TF coder, BYTE *user_key, size_t length){
    short N = 128;

    char temp_key[N];

    //Filling with 0
    for(int i = 0; i < N; i++){
        temp_key[i] = ( i < length ) ? user_key[i] : 0;
    }

    //Initialization of variables
    coder.k = N / 64;

    BYTE RS[4][8] = {
            {0x01, 0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E},
            {0xA4, 0x56, 0x82, 0xF3, 0x1E, 0xC6, 0x68, 0xE5},
            {0x02, 0xA1, 0xFC, 0xC1, 0x47, 0xAE, 0x3D, 0x19},
            {0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E, 0x03}
    };
    UINT *Me[coder.k];
    UINT *Mo[coder.k];

    for(int c1 = 0, c2 = 0, i = 0; i < 2 * coder.k; i++){
        if (i % 2 == 0) {
            Me[c1] = 0;
            for (int j = 4*i, shift = 3 ; j < 4*(i+1); j++, shift--){
                *Me[c1] += temp_key[j] << (shift * 8);
            }
            c1++;
        } else {
            Mo[c2] = 0;
            for (int j = 4*i, shift = 3 ; j < 4*(i+1); j++, shift--){
                *Mo[c2] = temp_key[j] << (shift * 8);
            }
            c2++;
        }
    }

    UINT a [coder.k];
    coder.SBox = a;
    for( int i = 0; i < coder.k; i++){
        coder.SBox[coder.k - 1 - i] = 0;
        for (int j = 0; j < 4; j++){
            UINT v = 0;
            for (int t = 0; t < 8; t++){
                v += RS[j][t] * *temp_key[ 8*i + t ];
            }
            coder.SBox[coder.k - 1 - i] += ( v * (1 << (8 * j)));
        }
    }


    //generation 32bit keys
    UINT ro = (1 << 24) + (1 << 16) + (1 << 8) + 1;
    for(int i = 0; i < 20; i++){
        unsigned long long A = h( 2 * i * ro, (UINT *) Me, coder.k); //???
        unsigned long long B = h( (2 * i + 1) * ro, (UINT *) Mo, coder.k); //????
        B = ROL(B,8); //ROL
        coder.keys[2 * i] = (A + B) & 0xFFFFFFFF;
        coder.keys[2 * i + 1] = ROL(((A + 2 * B) & 0xFFFFFFFF), 9); //ROL
    }
}

unsigned long long h(UINT inputWord, const UINT *inputWordArray, short ArraySize){ //???
    BYTE x[4]; //splitted input word
    x[0] = (inputWord >> 24) & 0xFF;
    x[1] = (inputWord >> 16) & 0xFF;
    x[2] = (inputWord >> 8) & 0xFF;
    x[3] = inputWord & 0xFF;

    BYTE * b [ArraySize];
    BYTE **l = b; //splitted words of input array
    for (int i = 0; i < ArraySize; i++) {
        BYTE temporal[4];
        l[i] = temporal;
        l[i][0] = (inputWordArray[i] >> 24) & 0xFF;
        l[i][1] = (inputWordArray[i] >> 16) & 0xFF;
        l[i][2] = (inputWordArray[i] >> 8) & 0xFF;
        l[i][3] = inputWordArray[i] & 0xFF;
    }

    BYTE y[4] = {0};
    if (ArraySize == 4) {
        y[0] = q(x[0], 1) ^ l[3][0];
        y[1] = q(x[1], 0) ^ l[3][1];
        y[2] = q(x[2], 0) ^ l[3][2];
        y[3] = q(x[3], 1) ^ l[3][3];
    } else {
        y[0] = x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = x[3];
    }

    if (ArraySize >= 3) {
        y[0] = q(y[0], 1) ^ l[2][0];
        y[1] = q(y[1], 0) ^ l[2][1];
        y[2] = q(y[2], 0) ^ l[2][2];
        y[3] = q(y[3], 1) ^ l[2][3];
    } else {
        y[0] = x[0];
        y[1] = x[1];
        y[2] = x[2];
        y[3] = x[3];
    }
    //__________________qx_____________qx_____________qx
    y[0] = q((q((q(y[0], 0) ^ l[1][0]), 0) ^ l[0][0]), 1);
    y[1] = q((q((q(y[1], 1) ^ l[1][1]), 0) ^ l[0][1]), 0);
    y[2] = q((q((q(y[2], 0) ^ l[1][2]), 1) ^ l[0][2]), 1);
    y[3] = q((q((q(y[3], 1) ^ l[1][3]), 1) ^ l[0][3]), 0);

    BYTE MDS[4][4] = {
            {0x01, 0xEF, 0x5B, 0x5B},
            {0x5B, 0xEF, 0xEF, 0x01},
            {0xEF, 0x5B, 0x01, 0xEF},
            {0xEF, 0x01, 0xEF, 0x5B}
    };

    unsigned long long H = 0;
    for (int j = 0; j < 4; j++){
        unsigned long long v = 0;
        for (int t = 0; t < 4; t++){
            v += MDS[j][t] * y[t];
        }
        H += v * ((unsigned long long)(1 << (8 * j)));
    }

    return H;
}

BYTE q(BYTE x, int op){
    assert( (op == 0) || (op == 1));
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

    //splitting byte into two nibbles
    BYTE a0 = x / 16;
    BYTE b0 = x % 16;

    BYTE a1 = a0 ^ b0;
    BYTE b1 = a0 ^ ROR4(b0) ^ ((8 * a0) % 16); //ROR4

    BYTE a2 = qt[op][0][a1];
    BYTE b2 = qt[op][1][b1];

    BYTE a3 = a2 ^ b2;
    BYTE b3 = a2 ^ ROR4(b2) ^ ((8 * a2) % 16);  //ROR4
    BYTE a4 = qt[op][2][a3];
    BYTE b4 = qt[op][3][b3];

    return (16*b4 + a4);
}

//Right circular shift for 4 least significant bits
BYTE ROR4(BYTE x){
    return (((x << 3) & 0xF) | ( (x & 0xF) >> 1));
}

//Left circular shift for unsigned int
UINT ROL(UINT x, BYTE shift){
    BYTE shl = shift % (sizeof(x)*8);
    if (shl == 0) return x;
    return ((x << shl) | (x >> (sizeof(x)*8 - shl)));
}

//Right circular shift for unsigned int
UINT ROR(UINT x, BYTE shift){
    BYTE shl = shift % (sizeof(x)*8);
    if (shl == 0) return x;
    return ((x >> shl) | (x << (sizeof(x)*8 - shl)));
}