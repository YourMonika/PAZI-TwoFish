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
        explicit TwoFish(BYTE *key);

        explicit TwoFish(const char *key);

        ~TwoFish();

        BYTE *twoFishCompilation(BYTE *plain);

       //  void decrypt();

    private:
        //static UINT *NtoP(const BYTE *plain);

        void keyShedule(const BYTE *global_k);

        static UINT gFunc(UINT inputWord, const UINT *inputWordArray, short arraySize);

        std::array<UINT, 2> fFunk(UINT R0, UINT R1, UINT round);

        static BYTE qBlock(BYTE block, int type);

        std::array<UINT, 2> PHT(UINT T0, UINT T1, UINT round);

        static BYTE ROR4(BYTE x);

        static UINT ROL(UINT x, BYTE shift);

        static UINT ROR(UINT x, BYTE shift);

        // static fields
        UINT keys[40]{};
        short k{};
        UINT *Sbox{};
    };
}
#endif //TWOFISH_TWOFISH_HPP
