//
// Created by MI on 16/12/2020
//

#include <array>
#include <utility>
#include "TwoFish.h"
#include "cmake-build-debug/TwoFish.h"


void encrypt(){

}

void decrypt(){

};


void twoFishCompilation() {
            /**
             * input
             * ntop
             * inputWhitening
             * F - function [16 rounds]
             * outputWhitening
             * result: chipher-text*/
}

void TwoFish::NtoP() {
            /**
             * Get 128-bit N, and divide it into 4 32-bit words p0, p1, p2, p3
             * also using for divide 128-bit key K to 32-bit word k0, k1, k2, k3
             * */

}

void TwoFish::inputWhite(BYTE plain_unit, BYTE key_unit) {
            /**
             * XORing(^) p0, p1, p2, p3 with k0, k1, k2, k3 by pairs
             *output is result presented like set of four 32-bit words R0, R1, R2, R3
             * */

}

void TwoFish::fFunk() {
            /**
             * Body of TwoFish's rounds
             * contains R0, R1 words and num r(round)
             * Input: 32-bit R0, R1 ; Output: 32-bit F0, F1
             * G-step: R0 passed to g-function an yields T0. R1 ROLing8 (<<8) and passed to g-function to yield T1
             * After goes PHT-block*/

}

void TwoFish::gFunc() {
            /**
             * First composite part of F - function. Heart of TwoFish
             * Input: 32-bit word
             * Output: 32-bit word
             * Transformation of R0, R1 before PHT in a round
             * Input splits in four 8-bit words (four bytes). Each byte goes through key-dependent S-boxes.
             * [4] S-box; Input: 8 bits; Output: 8 bits;
             * 4 results interpreted as vector[4] over GF(2**8), goes to MDS-box.*/


}

void TwoFish::SBox() {
            /**
             * Three 8-by-8-bit fixed permutations chosen from set of 2 possible: q0, q1
             * spaces between permutation - XOR with fixed keys from key KeyShedule S0, S1. Stays fixed due to decoding
             * Result goes to MDS**/


}

BYTE TwoFish::qBlock(BYTE block, bool type) { //may be troubles with BOOL --> char
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

void TwoFish::MDS() {
            /**
             * Input: array<8bit, 4> = four outputs after S-boxes
             * Output: Multiplication result if MDS-matrix on vector in Galos Field(2**8)
             * */
}

void TwoFish::combine(BYTE one, BYTE two) {
            /**Simple function of 2 nums.
             *Input:int a, b
             *Output: int c
             *c = a+b mod 2**32
             * */

}

void TwoFish::PHT() {
            /**
             * Second composite part of F - function.
             * Input: int a, b
             * a' = a + b mod 2**32
             * b' = a' + b mod 2**32
             * Output: a', b'
             * Output goes to combine with expanded key, from KeyShedule: K_2r+8 K_2r+9 // r - round number
             * */

}

void TwoFish::keyShedule(){
            /**
             * ?
             */

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


