#include <iostream>
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define Position(p) ((p) ? (p)->position : -1)
#define Size(p) ((p) ? (p)->size() : 0)
#define IsBlack(p) (!(p) || RB_BLACK == (p)->color)
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x)                                                                                                    \
    ((stature((x).lc) == stature((x).rc)) && ((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)))
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> struct BinNode {
    //数据
    T data;
    //父节点、孩子节点
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    //高度
    int height;
    //颜色
    RBColor color;
    //左式堆
    int npl;
    //层次
    int level;
    //打印位置
    int position;

    //构造
    BinNode()
        : parent(NULL)
        , lc(NULL)
        , rc(NULL)
        , height(0) {}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int height = 0)
        : data(e)
        , parent(p)
        , lc(lc)
        , rc(rc)
        , height(height) {}

    //以该节点为根的子树规模
    int size() {
        int s = 1;
        if (lc)
            s += lc->size();
        if (rc)
            s += rc->size();
        return s;
    }

    //插入
    // new BinNode不用带模板参数吗？
    BinNodePosi(T) insertAsLC(const T& e) { return lc = new BinNode(e, this); }
    BinNodePosi(T) insertAsRC(const T& e) { return rc = new BinNode(e, this); }

    //后继
    BinNodePosi(T) succ() {
        BinNodePosi(T) s = this;
        if (rc) {
            s = rc;
            while (HasLChild(*s))
                s = s->lc;
        } else {
            while (IsRChild(*s))
                s = s->parent;
            s = s->parent;
        }
        return s;
    }

    //比较器
    bool operator==(const BinNode& bn) { return data == bn.data; }
    bool operator<(const BinNode& bn) { return data < bn.data; }
};