#pragma once
#include "../../10-priorityQueue/PQ_ComplHeap.hpp"
#include "../_share/release.h"
#include "../fibonacci/Fibonacci.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <typeinfo>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector {
protected:
    //规模
    int _size;
    //容量
    int _capacity;
    //维护向量的数组
    T* _elem;

    //复制数组
    void copyFrom(const T* A, int lo, int hi) {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];
        }
    }

    //扩容
    void expand() {
        if (_size < _capacity)
            return;
        if (_capacity < DEFAULT_CAPACITY)
            _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; ++i)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

    //缩容
    void shrink() {
        if (_capacity < DEFAULT_CAPACITY)
            return;
        if (_size << 2 > _capacity)
            return;
        T* oldElem = _elem;
        _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; ++i)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

public:
    //默认构造，容量、规模、所有元素初始值
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }

    //用数组初始化
    Vector(const T* A, int n) { copyFrom(A, 0, n); }
    Vector(const T* A, int lo, int hi) { copyFrom(A, lo, hi); }

    //用向量初始化
    Vector(const Vector<T>& V) { copyFrom(V._elem, 0, V._size); }
    Vector(const Vector<T>& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }

    //析构
    ~Vector() { delete[] _elem; }

    //返回容量
    int capacity() { return _capacity; }
    //返回规模
    int size() { return _size; }

    //是否为空
    bool empty() { return _size <= 0; }

    //直接访问
    T& operator[](Rank r) const { return _elem[r]; }

    //重载=运算符
    Vector<T>& operator=(const Vector<T>& V) {
        if (_elem)
            delete[] _elem;
        copyFrom(V._elem, 0, V._size);
        return *this;
    }

    //查找，返回最后一次出现的位置
    Rank find(const T& e, Rank lo, Rank hi) const {
        while ((lo < hi--) && (e != _elem[hi]))
            ;
        return hi;
    }
    Rank find(const T& e) const { return find(e, 0, _size); }

    //插入，返回插入的位置
    Rank insert(Rank r, const T& e) {
        expand();
        for (int i = _size; i > r; --i)
            _elem[i] = _elem[i - 1];
        _elem[r] = e;
        ++_size;
        return r;
    }
    //在尾端插入
    Rank insert(const T& e) { return insert(_size, e); }

    //删除，返回删除元素的个数
    int remove(Rank lo, Rank hi) {
        if (lo == hi)
            return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    //返回删除元素的值
    T remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    //清空
    int clear() { return remove(0, _size); }

    //唯一化
    int deduplicate() {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size)
            find(_elem[i], 0, i) < 0 ? ++i : remove(i);
        return oldSize - _size;
    }

    //遍历：使用函数指针
    void traverse(void (*visit)(T&)) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }
    //使用函数对象
    template <typename VST> void traverse(VST visit) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }

    //判断是否有序，返回逆序对的数目
    int disordered() const {
        int n = 0;
        for (int i = 1; i < _size; ++i) {
            if (_elem[i - 1] > _elem[i])
                ++n;
            return n;
        }
    }

    //有序向量唯一化
    int uniquify() {
        Rank i = 0, j = 0;
        while (++j < _size) {
            if (_elem[i] != _elem[j])
                _elem[++i] = _elem[j];
        }
        _size = ++i;
        shrink();
        return j - i;
    }

    //有序向量查找
    Rank search(const T& e) { return search(e, 0, _size); }
    Rank search(const T& e, Rank lo, Rank hi) { return rand() % 2 ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); }
    //二分查找数组
    static Rank binSearch_low(T* A, const T& e, Rank lo, Rank hi) {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            if (e < A[mi])
                hi = mi;
            else if (A[mi] < e)
                lo = mi + 1;
            else
                return mi;
        }
        return -1;
    }
    // Fibonacci查找
    static Rank fibSearch(T* A, const T& e, Rank lo, Rank hi) {
        Fibnacci fib(hi - lo);
        while (lo < hi) {
            while (hi - lo < fib.get())
                fib.pre();
            Rank mi = lo + fib.get() - 1;
            if (e < A[mi])
                hi = mi;
            else if (A[mi] < e)
                lo = mi + 1;
            else
                return mi;
        }
        return -1;
    }
    //二分支的二分查找
    static Rank binSearch_high(T* A, const T& e, Rank lo, Rank hi) {
        while (1 < hi - lo) {
            Rank mi = (lo + hi) >> 1;
            e < A[mi] ? hi = mi : lo = mi;
        }
        return e == A[lo] ? lo : -1;
    }
    //带有语义的二分查找
    static Rank binSearch(T* A, const T& e, Rank lo, Rank hi) {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            e < A[mi] ? hi = mi : lo = mi + 1;
        }
        return --lo;
    }

    //排序
    void sort() { sort(0, _size); }
    void sort(Rank lo, Rank hi) {
        switch (rand() % 3) {
        case 1:
            bubbleSort(lo, hi);
            break;
        case 2:
            mergeSort(lo, hi);
            break;
        default:
            break;
        }
    }
    //冒泡排序
    void bubbleSort(Rank lo, Rank hi) {
        while (lo < hi = bubble(lo, hi))
            ;
    }
    Rank bubble(Rank lo, Rank hi) {
        Rank last = lo;
        while (++lo < hi) {
            if (_elem[lo - 1] > _elem[lo]) {
                last = lo;
                swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return last;
    }
    //归并排序
    void mergeSort() { mergeSort(0, _size); }
    void mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2)
            return;
        int mi = (lo + hi) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }
    void merge(Rank lo, Rank mi, Rank hi) {
        T* A = _elem + lo;
        int lb = mi - lo;
        T* B = new T[lb];
        for (Rank i = 0; i < lb; B[i] = A[i++])
            ;
        int lc = hi - mi;
        T* C = _elem + mi;
        for (Rank i = 0, j = 0, k = 0; j < lb;) {
            if (lc <= k || B[j] <= C[k])
                A[i++] = B[j++];
            if (k < lc && C[k] < B[j])
                A[i++] = C[k++];
        }
        delete[] B;
    }
    //堆排序
    void heapSort(Rank lo, Rank hi) {
        PQ_ComplHeap<T> H(_elem + lo, hi - lo);
        while (!H.empty())
            _elem[--hi] = H.delMax();
    }
    //快速排序
    void quickSort(Rank lo, Rank hi) {
        if (hi - lo < 2)
            return;
        Rank mi = partition(lo, hi - 1);
        quickSort(lo, mi);
        quickSort(mi + 1, hi);
    }
    Rank partition(Rank lo, Rank hi) {
        swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
        T pivot = _elem[lo];
        while (lo < hi) {
            while (lo < hi && pivot < _elem[hi])
                --hi;
            _elem[lo] = _elem[hi];
            while (lo < hi && pivot > _elem[lo])
                ++lo;
            _elem[hi] = _elem[lo];
        }
        _elem[lo] = pivot;
        return lo;
    }
};