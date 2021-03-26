#include <bitset>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define POW(c) (1 << (c))
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))

int main() {
    string s = "abcd";
    cout << s.length() << endl;
    system("pause");
    return 0;
}