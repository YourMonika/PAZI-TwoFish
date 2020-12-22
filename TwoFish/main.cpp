#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include "cmake-build-debug/TwoFish.hpp"

using namespace std;
using namespace tf;
int main(/*int argc, char* argv[]*/) {
    char key[] = "1231412412522";
    TwoFish tf(key);
    BYTE block[16] = {12, 42};
    BYTE text[8];
    tf.twoFishCompilation(block);
    for(size_t i=0; i < sizeof(tf.twoFishCompilation(block)); i++){
        text[i] = tf.twoFishCompilation(block)[i];
        cout << text[i] << endl;
    }

    return 0;
}