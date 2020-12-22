//
// Created by MI on 21.12.2020.
//

#ifndef TWOFISH_TWOFISH_HPP
#define TWOFISH_TWOFISH_HPP

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#include <array>
namespace tf {
    class TwoFish {
    public:
        TwoFish(BYTE *key);

        TwoFish(char *key);

        ~TwoFish();

        BYTE *twoFishCompilation(BYTE *plain);

        void decrypt();

    private:
        UINT *NtoP(BYTE *plain);

        void keyShedule(BYTE *global_k);

        UINT gFunc(UINT inputWord, UINT *inputWordArray, short arraySize);

        std::array<UINT, 2> fFunk(UINT R0, UINT R1, UINT round);

        BYTE qBlock(BYTE block, bool type);

        std::array<UINT, 2> PHT(UINT T0, UINT T1, UINT round);

        BYTE ROR4(BYTE x);

        UINT ROL(UINT x, BYTE shift);

        UINT ROR(UINT x, BYTE shift);

        // static fields
        UINT keys[40];
        short k;
        UINT *Sbox;
    };
}
#endif //TWOFISH_TWOFISH_HPP
