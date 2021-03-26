#include <iostream>
#include <windows.h>
using namespace std;

void hailstone(int n) {
    if (n > 1) {
        cout << n << " ";
        (n % 2) ? hailstone(3 * n + 1) : hailstone(n / 2);
    } else
        cout << n << endl;
}

int main() {
    for (int i = 1;; ++i) {
        cout << "hailstone " << i << ":" << endl;
        if (i % 10000 == 0)
            Sleep(10000);
        hailstone(i);
    }
    return 0;
}