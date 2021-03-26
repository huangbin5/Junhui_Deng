#include "Stack.hpp"
#include <iostream>
using namespace std;

int main() {
    Stack<int> s;
    s.push(3);
    s.push(4);
    s.pop();
    cout << s.top() << endl;
    system("pause");
    return 0;
}