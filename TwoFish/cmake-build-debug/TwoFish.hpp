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

class TwoFish{
public:
    void keyShedule();

private:
    UINT gFunc(UINT R, UINT round)
    std::array<UINT, 2> fFunk(UINT R0, UINT R1, UINT round);
    BYTE qBlock(BYTE block, bool type);
    std::array<UINT, 2> PHT(UINT T0, UINT T1, UINT round);
    BYTE ROR4(BYTE x);
    UINT ROL(UINT x, BYTE shift);
    UINT ROL(UINT x, BYTE shift);
};

#endif //TWOFISH_TWOFISH_HPP
