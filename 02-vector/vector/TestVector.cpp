#include "Vector.hpp"
#include <iostream>
using namespace std;

template <typename T> struct Increase {
    virtual void operator()(T& e) { ++e; }
};

template <typename T> void increase(Vector<T>& V) { V.traverse(Increase<T>()); }

int main() {
    Vector<int> v;
    increase(v);
    system("pause");
    return 0;
}

//带有模板的多文件编译要将声明和定义放在一块