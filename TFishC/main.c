#include <stdio.h>
#include "T2F.h"


int main() {
    UINT plain[4] = {0x00, 0x00, 0x00, 0x00};
    BYTE M[16] = {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}; // globalkey
    printf("Key : ");
    for(int i = 0; i < 16; i++){
        printf("%d", M[i]);
    }
    printf("\n");
    UINT gM[4] = {BYTES_TO_UINT(M[0], M[1], M[2], M[3]),
                  BYTES_TO_UINT(M[4], M[5], M[6], M[7]),
                  BYTES_TO_UINT(M[8], M[9], M[10], M[11]),
                  BYTES_TO_UINT(M[12], M[13], M[14], M[15])};
    keyS keySh;

    printf("Creating KeyShedule\n");
    keyShedule((const BYTE *) M, keySh);
    for(int j = 0; j < 40; j++){
        printf("Kkey[%i] = %lu\n", j, keySh.Kkey[j]);
    }
    printf("Finished KeyShedule, start encryption\n");

    UINT chipher[4];
    encryption(plain, keySh, chipher);
    printf("Printing chipher \n");
    for(int i = 0; i < 4; i++){
        printf("R[%i] = %i\n", i, (UINT) chipher[i]);
    }


    printf("Start decryption \n");
    UINT what_is_it[4];
    decryption(chipher, keySh, what_is_it);
    for(int i = 0; i < 4; i++){
        printf("R[%i] = %i\n", i, (UINT) what_is_it[i]);
    }

    return 0;
}