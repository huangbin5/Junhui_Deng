#include "../stack/Stack.hpp"
#include <iostream>
using namespace std;

bool paren(const char exp[], int lo, int hi) {
    Stack<char> s;
    for (int i = lo; i < hi; ++i) {
        if ('(' == exp[i])
            s.push(exp[i]);
        else if (!s.empty())
            s.pop();
        else
            return false;
    }
    return s.empty();
}

int main() {
    char exp[] = "(()()()";
    cout << paren(exp, 0, sizeof(exp) - 1) << endl;
    system("pause");
    return 0;
}