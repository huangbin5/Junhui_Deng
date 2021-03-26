#include "../../02-vector/vector/Vector.hpp"

template <typename T> class Stack : public Vector<T> {
public:
    void push(const T& e) { Vector<T>::insert(Vector<T>::size(), e); }

    T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }

    T& top() { return (*this)[Vector<T>::size() - 1]; }
};

//调用父类不写类名的话一定要用this->吗？
// this->insert(this->size(), e);