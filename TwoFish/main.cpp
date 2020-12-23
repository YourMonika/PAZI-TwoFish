#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include "cmake-build-debug/TwoFish.hpp"
#include <fstream>

using namespace std;
using namespace tf;
int main(/*int argc, char* argv[]*/) {
    BYTE key[16] = {0x34, 0x56, 0xFD, 0x41, 0x94, 0xA4, 0x38, 0x40,  0x2C, 0xB5, 0x78, 0x82, 0x12, 0x21, 0x6D, 0x27};
    TwoFish tf(key);
    BYTE block[16] = {0x34, 0x56, 0xFD, 0x41, 0x94, 0xA4, 0x38, 0x40,  0x2C, 0xB5, 0x78, 0x82, 0x12, 0x21, 0x6D, 0x27};
    //FILE "text.txt";
    tf.twoFishCompilation(block);
    for(size_t i=0; i < sizeof(tf.twoFishCompilation(block)); i++){
        cout << tf.twoFishCompilation(block)[i];
    }

    return 0;
}