#include "../stack/Stack.hpp"
#include <iostream>
using namespace std;

void convert(Stack<char>& s, __int64 n, int base) {
    static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    while (n > 0) {
        int tmp = n % base;
        s.push(digit[tmp]);
        n /= base;
    }
}

int main() {
    Stack<char> s;
    convert(s, 234, 2);
    while (!s.empty()) {
        printf("%c", s.pop());
    }
    puts("");
    system("pause");
    return 0;
}