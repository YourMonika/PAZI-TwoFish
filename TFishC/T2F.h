//
// Created by MI on 18.01.2021.
//

#ifndef TFISHC_T2F_H
#define TFISHC_T2F_H
#ifndef UINT
typedef unsigned long int UINT; //
#endif

#ifndef BYTE
typedef unsigned char BYTE; // 0 - 256
#endif

#define RHO 0x01010101L
#define ROL(x,n) (((x) << ((n) & 0x1F)) | ((x) >> (32-((n) & 0x1F))))
#define ROR(x,n) (((x) >> ((n) & 0x1F)) | ((x) << (32-((n) & 0x1F))))


typedef struct {
    UINT Kkey[40];
    UINT Skey[2];
} keyS;

// --MUTA-FUNCTIONS--
BYTE b0(UINT x);
BYTE b1(UINT x);
BYTE b2(UINT x);
BYTE b3(UINT x);
UINT BYTES_TO_UINT(BYTE x0, BYTE x1, BYTE x2, BYTE x3);
UINT BYTEARRAY_TO_UINT(const BYTE *x);

// --Polynomial const operations--
UINT polyMul(UINT A, UINT B);
UINT gfMOD(UINT A, UINT modulus);

// --G-block--
BYTE q(BYTE x, int op);
UINT g(UINT X, UINT S[2]);

// --ROUND--
void ROUNDENCRYPT(UINT R[4], int round, keyS keys);
void ROUNDDECRYPT(UINT R[4], int round, keyS keys);
void encryption(const UINT plain[4], keyS keys, UINT R[4]);
void decryption(const UINT chipher[4], keyS keys, UINT R[4]);

// RSMatrix Multiplying FOR S00 - S03 S10-S13 - Keys
UINT RSM(BYTE sd[8]);

// Generating keys
void pushSkeys(const BYTE globalkey[16], keyS key); // creating S-set-keys for Key Shedule
void pushKkeys(const BYTE globalkey[16], keyS key); // creating K-set-keys for Key Shedule
void keyShedule(const BYTE globalkey[16], keyS key);

// --Shifts--
BYTE ROR4(BYTE x);
/*
UINT ROR(UINT x, BYTE shift);
UINT ROL(UINT x, BYTE shift);
 */
#endif //TFISHC_T2F_H
