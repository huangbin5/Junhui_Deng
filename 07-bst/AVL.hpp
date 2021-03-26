#include "BST.hpp"
#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
#define tallerChild(x)                                                                                                           \
    (stature((x)->lc) > stature((x)->rc) ? (x)->lc                                                                               \
                                         : (stature((x)->lc) < stature((x)->rc) ? (x)->rc : IsLChild(*(x)) ? (x)->lc : (x)->rc))

template <typename T> class AVL : public BST<T> {
public:
    BinNodePosi(T) insert(const T& e) {
        BinNodePosi(T)& x = search(e);
        if (x)
            return x;
        x = new BinNode<T>(e, _hot);
        ++_size;
        for (BinNodePosi(T) g = _hot; g; g = g->parent) {
            if (!AvlBalanced(*g)) {
                FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
                break;
            } else
                updateHeight(g);
        }
        return x;
    }
    bool remove(const T& e) {
        BinNodePosi(T)& x = search(e);
        if (!x)
            return false;
        removeAt(x, _hot);
        --_size;
        for (BinNodePosi(T) g = _hot; g; g = g->parent) {
            if (!AvlBalanced(*g))
                g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            updateHeight(g);
        }
        return true;
    }
};