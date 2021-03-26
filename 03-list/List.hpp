#pragma once
#include "ListNode.hpp"

template <typename T> class List {
private:
    //大小
    int _size;
    //头尾
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    //初始化
    void init() {
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        header->succ = trailer;
        header->pred = NULL;
        trailer->pred = header;
        trailer->succ = NULL;
        _size = 0;
    }

    //复制节点p开始的n项
    void copyNodes(ListNodePosi(T) p, int n) {
        init();
        while (n--) {
            insertAsLast(p->data);
            p = p->succ;
        }
    }

public:
    //构造
    List() { init(); }
    List(const List<T>& L) { copyNodes(L.first(), L.size()); }
    List(const List<T>& L, Rank r, int n) {
        ListNodePosi(T) p = L.first();
        while (0 < r--)
            p = p->succ;
        copyNodes(p, n);
    }
    List(ListNodePosi(T) p, int n) { copyNodes(p, n); }

    //析构
    ~List() {
        clear();
        delete header;
        delete trailer;
    }

    //大小
    int size() const { return _size; }
    bool empty() const { return _size <= 0; }

    //清空
    int clear() {
        int oldSize = _size;
        while (0 < _size)
            remove(header->succ);
        return oldSize;
    }

    //首末节点
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return trailer->pred; }

    //循秩访问
    T& operator[](Rank r) const {
        ListNodePosi(T) p = first();
        while (0 < r--)
            p = p->succ;
        return p->data;
    }

    //是否合法
    bool valid(ListNodePosi(T) p) { return p && p != header && p != trailer; }

    //无序列表查找
    ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const {
        while (n--) {
            if (e == (p = p->pred)->data)
                return p;
        }
        return NULL;
    }

    //插入
    ListNodePosi(T) insertAsFirst(const T& e) {
        ++_size;
        return header->insertAsSucc(e);
    }
    ListNodePosi(T) insertAsLast(const T& e) {
        ++_size;
        return trailer->insertAsPred(e);
    }
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& e) {
        ++_size;
        return p->insertAsSucc(e);
    }
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& e) {
        ++_size;
        return p->insertAsPred(e);
    }

    //删除
    T remove(ListNodePosi(T) p) {
        T e = p->data;
        p->succ->pred = p->pred;
        p->pred->succ = p->succ;
        delete p;
        --_size;
        return e;
    }

    //唯一化
    int deduplicate() {
        if (_size < 2)
            return 0;
        int oldSize = _size;
        ListNodePosi(T) p = header;
        int r = 0;
        while (trailer != (p = p->succ)) {
            ListNodePosi(T) q = find(p->succ, r, p);
            q ? remove(q) : ++r;
        }
        return oldSize - _size;
    }

    //遍历：函数指针
    void traverse(void (*visit)(T&)) {
        for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
            visit(p->data);
    }
    //遍历：函数对象
    template <typename VST> void traverse(VST& visit) {
        for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
            visit(p->data);
    }

    //有序列表唯一化
    int uniquify() {
        if (_size < 2)
            return 0;
        int oldSize = _size;
        ListNodePosi(T) p = first();
        ListNodePosi(T) q;
        while (trailer != (q = p->succ)) {
            if (p->data != q->data)
                p = q;
            else
                remove(q);
        }
        return oldSize - _size;
    }

    //有序列表查找
    ListNodePosi(T) search(const T& e, int n, ListNodePosi(T) p) {
        while (0 < n--)
            if ((p = p->pred)->data <= e)
                break;
        return p;
    }

    //排序
    void sort() { sort(first(), _size); }
    void sort(ListNodePosi(T) p, int n) {
        switch (rand() % 3) {
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
        }
    }
    //插入排序
    void insertionSort(ListNodePosi(T) p, int n) {
        for (int r = 0; r < n; ++r) {
            insertAfter(search(p->data, r, p), p->data);
            p = p->succ;
            remove(p->pred);
        }
    }
    //选择排序
    void selectionSort(ListNodePosi(T) p, int n) {
        ListNodePosi(T) head = p->pred;
        ListNodePosi(T) tail = p;
        for (int i = 0; i < n; ++i)
            tail = tail->succ;
        while (1 < n) {
            ListNodePosi(T) max = selectMax(head->succ, n);
            insertBefore(tail, remove(max));
            tail = tail->pred;
            --n;
        }
    }
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) {
        ListNodePosi(T) max = p;
        for (ListNodePosi(T) cur = p; n > 1; --n) {
            if ((cur = cur->succ)->data >= max->data)
                max = cur;
        }
        return max;
    }
    //归并排序
    void mergeSort(ListNodePosi(T) & p, int n) {
        if (n < 2)
            return;
        int m = n >> 1;
        ListNodePosi(T) q = p;
        for (int i = 0; i < m; ++i)
            q = q->succ;
        mergeSort(p, m);
        mergeSort(q, n - m);
        merge(p, m, q, n - m);
    }
    void merge(ListNodePosi(T) & p, int n, ListNodePosi(T) q, int m) {
        ListNodePosi(T) pp = p->pred;
        while (0 < m) {
            if (0 < n && p->data <= q->data) {
                if (q == (p = p->succ))
                    break;
                --n;
            } else {
                insertBefore(p, remove((q = q->succ)->pred));
                --m;
            }
        }
        p = pp->succ;
    }
};