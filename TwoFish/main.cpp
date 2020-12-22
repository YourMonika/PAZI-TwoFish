#include <iostream>
#include <string>
#include <array>

using namespace std;
int main(/*int argc, char* argv[]*/) {
    int a;
    cin >> a;
    cout << a << endl;
    array<int, 4> p;

    for(int i = 0;i<4;i++)
    {
        p[i] = a & (15 << (4*i));
        cout << (p[i]) << endl;
//        cout << i << endl;
    }

    return 0;
}