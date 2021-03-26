#include "../05-bintree/BinTree.hpp"
#include "PQ.hpp"

template <typename T> static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) {
    if (!a)
        return b;
    if (!b)
        return a;
    if (lt(a->data, b->data))
        swap(a, b);
    a->rc = merge(a->rc, b);
    a->rc->parent = a;
    if (!a->lc || a->lc->npl < a->rc->npl)
        swap(a->lc, a->rc);
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
}

template <typename T> class PQ_LeftHeap : public PQ<T>, public BinTree<T> {
public:
    PQ_LeftHeap() {}
    PQ_LeftHeap(T* E, int n) {
        for (int i = 0; i < n; ++i)
            insert(E[i]);
    }

    T getMax() { return _root->data; }
    void insert(T e) {
        BinNodePosi(T) v = new BinNode<T>(e);
        _root = merge(_root, v);
        _root->parent = NULL;
        ++_size;
    }
    T delMax() {
        BinNodePosi(T) lHeap = _root->lc;
        BinNodePosi(T) rHeap = _root->rc;
        T e = _root->data;
        delete _root;
        --_size;
        _root = merge(lHeap, rHeap);
        if (_root)
            _root->parent = NULL;
        return e;
    }
};