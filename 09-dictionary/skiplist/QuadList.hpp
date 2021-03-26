#include "QuadListNode.hpp"

template <typename T> class QuadList {
private:
    int _size;
    QlistNodePosi(T) header;
    QlistNodePosi(T) trailer;

protected:
    void init() {
        header = new QuadListNode<T>;
        trailer = new QuadListNode<T>;
        header->succ = trailer;
        header->pred = NULL;
        trailer->pred = header;
        trailer->succ = NULL;
        header->above = trailer->above = NULL;
        header->below = trailer->below = NULL;
        _size = 0;
    }
    int clear() {
        int oldSize = _size;
        while (_size > 0)
            remove(header->succ);
        return oldSize;
    }

public:
    QuadList() { init(); }
    ~QuadList() {
        clear();
        delete header;
        delete trailer;
    }

    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    QlistNodePosi(T) first() const { return header->succ; }
    QlistNodePosi(T) last() const { return trailer->pred; }
    bool valid(QlistNodePosi(T) p) { return p && (trailer != p) && (header != p); }

    QlistNodePosi(T) insertAfterAbove(const T& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL) {
        ++_size;
        return p->insertAsSuccAbove(e, b);
    }
    T remove(QlistNodePosi(T) p) {
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        --_size;
        T e = p->entry;
        delete p;
        return e;
    }

    void traverse(void (*)(T&));
    template <typename VST> void travser(VST&);
};