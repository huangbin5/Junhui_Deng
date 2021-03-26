#include "../02-vector/vector/Vector.hpp"
#include "PQ.hpp"
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
#define Parent(i) ((i - 1) >> 1)
#define LastInternal(n) Parent(n - 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define ParentValid(i) (0 < i)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)
#define ProperParent(PQ, n, i)                                                                                                   \
    (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))

template <typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T> {
protected:
    Rank percolateUp(Rank i) {
        while (ParentValid(i)) {
            Rank j = Parent(i);
            if (lt(_elem[i], _elem[j]))
                break;
            swap(_elem[i], _elem[j]);
            i = j;
        }
        return i;
    }
    Rank percolateDown(Rank n, Rank i) {
        Rank j;
        while (i != (ProperParent(_elem, n, i))) {
            swap(_elem[i], _elem[j]);
            i = j;
        }
        return i;
    }
    void heapify(Rank n) {
        for (int i = LastInternal(n); InHeap(n, i) l-- i)
            percolateDown(n, i);
    }

public:
    PQ_ComplHeap() {}
    PQ_ComplHeap(T* A, Rank n) {
        copyFrom(A, 0, n);
        heapify(n);
    }

    T getMax() { return _elem[0]; }
    void insert(T e) {
        Vector<T>::insert(e);
        percolateUp(_size - 1);
    }
    T delMax() {
        T maxElem = _elem[0];
        _elem[0] = _elem[--_size];
        percolateDown(_size, 0);
        return maxElem;
    }
};