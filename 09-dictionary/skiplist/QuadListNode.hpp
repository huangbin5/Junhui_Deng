#include <iostream>
#define QlistNodePosi(T) QuadListNode<T>*

template <typename T> struct QuadListNode {
    T entry;
    QlistNodePosi(T) pred;
    QlistNodePosi(T) succ;
    QlistNodePosi(T) above;
    QlistNodePosi(T) below;

    QuadListNode(
        T e = T(), QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL, QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL)
        : entry(e)
        , pred(p)
        , succ(s)
        , above(a)
        , below(b) {}

    QlistNodePosi(T) insertAsSuccAbove(const T& e, QlistNodePosi(T) b = NULL) {
        QlistNodePosi(T) x = new QuadListNode<T>(e, this, succ, NULL, b);
        succ->pred = x;
        succ = x;
        if (b)
            b->above = x;
        return x;
    }
};