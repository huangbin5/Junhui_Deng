#pragma once
#include <iostream>

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode {
    //数据
    T data;
    //前驱
    ListNodePosi(T) pred;
    //后继
    ListNodePosi(T) succ;

    //构造
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data(e)
        , pred(p)
        , succ(s) {}

    //插入
    ListNodePosi(T) insertAsPred(const T& e) {
        ListNodePosi(T) x = new ListNode(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }
    ListNodePosi(T) insertAsSucc(const T& e) {
        ListNodePosi(T) x = new ListNode(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};