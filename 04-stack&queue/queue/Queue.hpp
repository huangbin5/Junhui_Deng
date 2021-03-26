#include "../../03-list/List.hpp"

template <typename T> class Queue : public List<T> {
public:
    void enqueue(const T& e) { List<T>::insertAsLast(e); }

    T dequeue() { return List<T>::remove(List<T>::first()); }

    T& front() { return List<T>::first()->data; }

    T& rear() { return List<T>::last()->data; }
};