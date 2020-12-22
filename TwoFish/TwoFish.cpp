#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by MI on 16/12/2020
//

#include <array>
#include <iostream>
#include "cmake-build-debug/TwoFish.hpp"

using namespace tf;
TwoFish::TwoFish(BYTE *key){
    TwoFish::keyShedule(key);
}

TwoFish::TwoFish(const char *key){
    BYTE *u_key = new BYTE[size_t(key)];
    for (size_t i=0;i < sizeof(key); i++){
        u_key[i] = (BYTE) key[i];
    }
    TwoFish::keyShedule(u_key);
}

TwoFish::~TwoFish(){
    delete [] TwoFish::Sbox;
}
/**
void TwoFish::decrypt(){

};
*/

BYTE *TwoFish::twoFishCompilation(BYTE *plain) {
    /**
             * creating keyShedule
             * ntop
             * inputWhitening
             * F - function [16 rounds]
             * outputWhitening
    * result: chipher-text*/
    UINT P0, P1, P2, P3;
    P0 = (plain[0] << 24) + (plain[1] << 16) + (plain[2] << 8) + plain[3];
    P1 = (plain[4] << 24) + (plain[5] << 16) + (plain[6] << 8) + plain[7];
    P2 = (plain[8] << 24) + (plain[9] << 16) + (plain[10] << 8) + plain[11];
    P3 = (plain[12] << 24) + (plain[13] << 16) + (plain[14] << 8) + plain[15];
    UINT P[4] = {P0, P1, P2, P3};

/** I W */
    for(int i = 0; i < 4; i++){
        P[i] ^= TwoFish::keys[i];
    }

    for(int i = 0; i < 16; i++){
        std::array temp_pp = fFunk(P[0], P[1], i);
        temp_pp[0] = ROR(P[2]^temp_pp[0] , 1);
        temp_pp[1] = ROL(P[3], 1)^temp_pp[1];
        P[0] = P[2];
        P[1] = P[3];
        P[2] = temp_pp[0];
        P[3] = temp_pp[1];
    }
/** O W */
    for(int i = 0; i < 4; i++){
        P[i] ^= TwoFish::keys[i+4];
    }

    for (int i = 0; i < 16; i++){
        plain[i] = (P[(i/4)] >> (24 - 8*(i - 4* (i/4)))) & 0xFF;
        std::cout << plain[i];
    }

    return plain;
}

/**UINT *TwoFish::NtoP(const BYTE *plain) {

             * Get 128-bit N, and divide it into 4 32-bit words p0, p1, p2, p3
             * also using for divide 128-bit key K to 32-bit word k0, k1, k2, k3
    * *
    UINT P0, P1, P2, P3;
    P0 = (plain[0] << 24) + (plain[1] << 16) + (plain[2] << 8) + plain[3];
    P1 = (plain[4] << 24) + (plain[5] << 16) + (plain[6] << 8) + plain[7];
    P2 = (plain[8] << 24) + (plain[9] << 16) + (plain[10] << 8) + plain[11];
    P3 = (plain[12] << 24) + (plain[13] << 16) + (plain[14] << 8) + plain[15];

    UINT P[4] = {P0, P1, P2, P3};

    return P;
}
*/

void TwoFish::keyShedule(const BYTE *global_k){
    /**
     * done only for 128-bit.
     * Input: Global Key 128-bit as BYTE *
     * Output: void
     * Fulfill keys[40] keys, Sbox keys, Whitening I|O keys
             * ?
    */
    BYTE temporal_k[128];

    for(int i = 0; i < 128; i++){
        temporal_k[i] = ( i < sizeof(global_k) ) ? global_k[i] : 0;
    }
    TwoFish::k = 2;

    BYTE RS[4][8] = {

            {0x01, 0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E},
            {0xA4, 0x56, 0x82, 0xF3, 0x1E, 0xC6, 0x68, 0xE5},
            {0x02, 0xA1, 0xFC, 0xC1, 0x47, 0xAE, 0x3D, 0x19},
            {0xA4, 0x55, 0x87, 0x5A, 0x58, 0xDB, 0x9E, 0x03}
    };
// prepon to g - function.
    UINT *Me = new UINT[k];
    UINT *Mo = new UINT[k];

    for(int i1 = 0, i2 = 0, i = 0; i < 2 * TwoFish::k; i++){
        if (i % 2 == 0){
            Me[i1] = 0;
            for (int j = 4*i, shift = 3 ; j < 4*(i+1); j++, shift--){
                Me[i1] += (temporal_k[j] << (shift * 8));
            }
            i1++;
        }
        else{
            Mo[i2] = 0;
            for (int j = 4*i, shift = 3; j < 4*(i+1); j++, shift-- ){
                Mo[i2] = temporal_k[j] << (shift * 8);
            }
            i2++;
        }

    }
// filling Sbox for qBlock and BYTE Sbox()
    TwoFish::Sbox = new UINT[k];
    for(int i = 0; i < k; i++){
        TwoFish::Sbox[k - 1 - i] = 0;
        for(int j = 0; j < 4; j++){
            UINT v = 0;
            for(int t = 0; t < 8; t++){
                v += RS[j][t] * temporal_k[8*i+t];
            }
            TwoFish::Sbox[k - 1 - i] += (v*(1 << (8*j)));
        }
    }

    UINT ro = (1 << 24) + (1 << 16) + (1 << 8) + 1;
    for(int i = 0; i < 20; i++){
        UINT A = TwoFish::gFunc( 2 * i * ro, Me, TwoFish::k);
        UINT B = TwoFish::gFunc( (2 * i + 1) * ro, Mo, TwoFish::k);
        B = ROL(B,8);
        keys[2 * i] = ((A + B) & 0xFFFFFFFF);
        keys[2 * i + 1] = (ROL(((A + 2 * B) & 0xFFFFFFFF), 9));
    }
}

std::array<UINT, 2> TwoFish::fFunk(UINT R0, UINT R1, UINT round) {
    /**
             * Body of TwoFish's rounds
             * contains R0, R1 words and num r(round)
             * Input: 32-bit R0, R1 ; Output: 32-bit F0, F1
             * G-step: R0 passed to g-function an yields T0. R1 ROLing8 (<<8) and passed to g-function to yield T1
             * PHT: -- PHT --
             * Addition mod 2**32: -- PHT --
             * Repeat for 16 time in Full Compilation
    * */

    R0 = TwoFish::gFunc(R0, TwoFish::Sbox, TwoFish::k);
    R1 = TwoFish::gFunc(TwoFish::ROL(R1, 8 ), TwoFish::Sbox, TwoFish::k);
    std::array<UINT, 2> T = TwoFish::PHT(R0, R1, round); //include addition mod 2**32 (actually, not realized// soon)

    return T;
}


UINT TwoFish::gFunc(UINT R, const UINT *sbox, short arraySize) {
    /**
             * First composite part of F - function. Heart of TwoFish
             * Input: 32-bit word
             * Output: 32-bit word
             * Transformation of R0, R1 before PHT in a round
             * Input splits in four 8-bit words (four bytes). Each byte goes through key-dependent S-boxes.
             * [4] S-box; Input: 8 bits; Output: 8 bits;
    * 4 results interpreted as vector[4] over GF(2**8), goes to MDS-box.*/
    BYTE x[4]; //splitted input word
    x[0] = (R >> 24) & 0xFF;
    x[1] = (R >> 16) & 0xFF;
    x[2] = (R >> 8) & 0xFF;
    x[3] = R & 0xFF;

    BYTE **l = new BYTE*[arraySize];

    for (int i = 0; i < arraySize; i++) {
        l[i] = new BYTE[4];
        l[i][0] = (sbox[i] >> 24) & 0xFF;
        l[i][1] = (sbox[i] >> 16) & 0xFF;
        l[i][2] = (sbox[i] >> 8) & 0xFF;
        l[i][3] = sbox[i] & 0xFF;
    }

    BYTE y[4] = {0};
    y[0] = x[0];
    y[1] = x[1];
    y[2] = x[2];
    y[3] = x[3];


    /** Results of SBoxes */
    y[0] = TwoFish::qBlock((TwoFish::qBlock((TwoFish::qBlock(y[0], 0) ^ l[1][0]), 0) ^ l[0][0]), 1);
    y[1] = TwoFish::qBlock((TwoFish::qBlock((TwoFish::qBlock(y[1], 1) ^ l[1][1]), 0) ^ l[0][1]), 0);
    y[2] = TwoFish::qBlock((TwoFish::qBlock((TwoFish::qBlock(y[2], 0) ^ l[1][2]), 1) ^ l[0][2]), 1);
    y[3] = TwoFish::qBlock((TwoFish::qBlock((TwoFish::qBlock(y[3], 1) ^ l[1][3]), 1) ^ l[0][3]), 0);

    /** MDS - block */
    BYTE MDS[4][4] = {
            {0x01, 0xEF, 0x5B, 0x5B},
            {0x5B, 0xEF, 0xEF, 0x01},
            {0xEF, 0x5B, 0x01, 0xEF},
            {0xEF, 0x01, 0xEF, 0x5B}
    };
    /** Double function for key structuring and implementing results of MDS-block */
    UINT H = 0;
    for (int j = 0; j < 4; j++){
        UINT v = 0;
        for (int t = 0; t < 4; t++){
            v += MDS[j][t] * y[t];
        }
        H += v * ((UINT)(1 << (8 * j)));
    }

    return H;
}

BYTE TwoFish::qBlock(BYTE block, int type) { //may be troubles with BOOL --> char
    /**
             * Main part of S-boxes
             * Input: 8 bit, bool type - (False if q0-type, True if q1-type)
             * Output: 8 bit
             * Byte splits into two 4-bits nibble: a0, b0.
             * a1 = a0 XOR b0
             * b1 = a0 XOR (b0 >> 1) XOR (8 a0 mod 16)
    * */
    BYTE a0, a1, b0, b1;
    const BYTE qt[2][4][16] = {
            //q0
            {
                    { 0x8, 0x1, 0x7, 0xD, 0x6, 0xF, 0x3, 0x2, 0x0, 0xB, 0x5, 0x9, 0xE, 0xC, 0xA, 0x4 },
                    { 0xE, 0xC, 0xB, 0x8, 0x1, 0x2, 0x3, 0x5, 0xF, 0x4, 0xA, 0x6, 0x7, 0x0, 0x9, 0xD },
                    { 0xB, 0xA, 0x5, 0xE, 0x6, 0xD, 0x9, 0x0, 0xC, 0x8, 0xF, 0x3, 0x2, 0x4, 0x7, 0x1 },
                    { 0xD, 0x7, 0xF, 0x4, 0x1, 0x2, 0x6, 0xE, 0x9, 0xB, 0x3, 0x0, 0x8, 0x5, 0xC, 0xA }
            },
            //q1
            {
                    { 0x2, 0x8, 0xB, 0xD, 0xF, 0x7, 0x6, 0xE, 0x3, 0x1, 0x9, 0x4, 0x0, 0xA, 0xC, 0x5 },
                    { 0x1, 0xE, 0x2, 0xB, 0x4, 0xC, 0x3, 0x7, 0x6, 0xD, 0xA, 0x5, 0xF, 0x9, 0x0, 0x8 },
                    { 0x4, 0xC, 0x7, 0x5, 0x1, 0x6, 0x9, 0xA, 0x0, 0xE, 0xD, 0x8, 0x2, 0xB, 0x3, 0xF },
                    { 0xB, 0x9, 0x5, 0x1, 0xC, 0x3, 0xD, 0xE, 0x6, 0x4, 0x7, 0xF, 0x2, 0x0, 0x8, 0xA }
            },
    };

    a0 = block >> 4;
    b0 = block ^ 15;

    a1 = a0 ^ b0;
    b1 = a0 ^ ROR4(b0) ^ ((8 * a0) % 16);

    a0 = qt[type][0][a1];
    b0 = qt[type][1][b1]; /** I think I can DELETE tBlock, cause of t-tables, cause of t{0,1,2,3}*/

    a1 = a0 ^ b0;
    b1 = a0 ^ ROR4(b0) ^ ((8 * a0) % 16);

    a0 = qt[type][2][a1];
    b0 = qt[type][3][b1];

    return (16*b0 + a0);
}


std::array<UINT, 2> TwoFish::PHT(UINT T0, UINT T1, UINT round) {
    /**
             * Second composite part of F - function.
             * Input: int a, b
             * a' = a + b mod 2**32
             * b' = a' + b mod 2**32
             * Output: a', b'
             * Output goes to combine with expanded key, from KeyShedule: K_2r+8 K_2r+9 // r - round number
    * */
    T0 = (T0 + T1) % sizeof(UINT);
    T1 = (T0 + T1) % sizeof(UINT);

    T0 = (T0 + TwoFish::keys[2*round + 8]);
    T1 = (T1 + TwoFish::keys[2*round + 9]);

    std::array<UINT, 2> T = {T0, T1};

    return T;
}

/** Circular shifts Left-Right*/

UINT TwoFish::ROL(UINT x, BYTE shift){
    BYTE shl = shift % (sizeof(x)*8);
    if (shl == 0) return x;
    return ((x << shl) | (x >> (sizeof(x)*8 - shl)));
}

UINT TwoFish::ROR(UINT x, BYTE shift){
    BYTE shl = shift % (sizeof(x)*8);
    if (shl == 0) return x;
    return ((x >> shl) | (x << (sizeof(x)*8 - shl)));
}

BYTE TwoFish::ROR4(BYTE x){
    /** Little function. Circular shift of UINT<4>. Used in SBOX - Q-permutation*/
    return (((x << 3) & 0xF) | ( (x & 0xF) >> 1));
}





#pragma clang diagnostic pop