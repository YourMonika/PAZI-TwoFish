#include <stdio.h>
#include "T2F.h"


int main() {
    /*   UINT plain[4] = {0, 0, 0, 0};
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
       */
       UINT K[40] = {0x52C54DDE, 0x11F0626D,
                     0x7CAC9D4A, 0x4D1B4AAA,
                     0xB7B83A10, 0x1E7D0BEB,
                     0xEE9C341F, 0xCFE14BE4,
                     0xF98FFEF9, 0x9C5B3C17,
                     0x15A48310, 0x342A4D81,
                     0x424D89FE, 0xC14724A7,
                     0x311B834C, 0xFDE87320,
                     0x3302778F, 0x26CD67B4,
                     0x7A6C6362, 0xC2BAF60E,
                     0x3411B994, 0xD972C87F,
                     0x84ADB1EA, 0xA7DEE434,
                     0x54D2960F, 0xA2F7CAA8,
                     0xA6B8FF8C, 0x8014C425,
                     0x6A748D1C, 0xEDBAF720,
                     0x928EF78C, 0x0338EE13,
                     0x9949D6BE, 0xC8314176,
                     0x07C07D68, 0xECAE7EA7,
                     0x1FE71844, 0x85C05C89,
                     0xF298311E, 0x696EA672};

        /*
       for(int j = 0; j < 40; j++){
        //   keySh.Kkey[j] = K[j];
           printf("Kkey[%i] = %lu\n", j, keySh.Kkey[j]);
       }
       printf("Finished KeyShedule, start encryption\n");

       UINT chipher[4];
       encryption(plain, keySh, chipher);
       printf("Printing chipher \n");
       for(int i = 0; i < 4; i++){
           printf("R[%i] = %x\n", i, (UINT) chipher[i]);
       }
       printf("%i", sizeof(UINT));


       printf("Start decryption \n");
       UINT what_is_it[4];
       decryption(chipher, keySh, what_is_it);
       for(int i = 0; i < 4; i++){
           printf("R[%i] = %i\n", i, (UINT) what_is_it[i]);
       }
   */

    /*
     * Testing q, g, h - funcs
     */
    UINT R[4] = {0, 0, 0, 0};

    R[0] = R[0]^K[0];
    R[1] = R[1]^K[1];
    R[2] = R[2]^K[2];
    R[3] = R[3]^K[3];

    printf("%lx, %lx, %lx, %lx", R[0], R[1], R[2], R[3]);

    return 0;
}