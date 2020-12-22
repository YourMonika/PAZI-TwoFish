//
// Created by MI on 21.12.2020.
//

#ifndef TWOFISH_TWOFISH_H
#define TWOFISH_TWOFISH_H

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

class TwoFish{
public:

private:


    void keyShedule();
    BYTE ROR4(BYTE x);
    UINT ROL(UINT x, BYTE shift);
    UINT ROL(UINT x, BYTE shift);
};

#endif //TWOFISH_TWOFISH_H
