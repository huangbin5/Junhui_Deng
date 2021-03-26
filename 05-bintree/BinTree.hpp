#include "../04-stack&queue/queue/Queue.hpp"
#include "../04-stack&queue/stack/Stack.hpp"
#include "BinNode.hpp"
using namespace std;

template <typename T> class BinTree {
protected:
    //规模
    int _size;
    //根
    BinNodePosi(T) _root;
    //树形打印时保存的数组
    Vector<char*> printArray;

    //更新节点高度
    virtual int updateHeight(BinNodePosi(T) x) { return x->height = 1 + max(stature(x->lc), stature(x->rc)); }
    //更新节点及其祖先的高度
    void updateHeightAbove(BinNodePosi(T) x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }

public:
    //构造析构
    BinTree()
        : _size(0)
        , _root(NULL) {}
    ~BinTree() {}

    //规模
    int size() const { return _size; }
    //是否为空
    bool empty() const { return !_root; }
    //树根
    BinNodePosi(T) root() const { return _root; }

    //插入
    BinNodePosi(T) insertAsRoot(const T& e) {
        _size = 1;
        return _root = new BinNode<T>(e);
    }
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, const T& e) {
        ++_size;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, const T& e) {
        ++_size;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }
    //接入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) {
        if (x->lc = S->_root)
            x->lc->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        //释放原树
        S->_root = NULL;
        S->_size = 0;
        release(S);
        S = NULL;
        return x;
    }
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) {
        if (x->rc = S->_root)
            x->rc->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = NULL;
        S->_size = 0;
        release(S);
        S = NULL;
        return x;
    }

    //删除
    int remove(BinNodePosi(T) x) {
        FromParentTo(*x) = NULL;
        updateHeightAbove(x->parent);
        int n = removeAt(x);
        _size -= n;
        return n;
    }
    static int removeAt(BinNodePosi(T) x) {
        if (!x)
            return 0;
        int n = 1 + removeAt(x->lc) + removeAt(x->rc);
        release(x->data);
        release(x);
        return n;
    }

    //子树分离
    BinTree<T>* secede(BinNodePosi(T) x) {
        FromParentTo(*x) = NULL;
        updateHeightAbove(x->parent);
        _size -= x->size();
        BinTree<T>* S = new BinTree<T>;
        S->root = x;
        x->parent = NULL;
        S->_size = x->size();
        return S;
    }

    //先序遍历
    template <typename VST> void travPre_R(BinNodePosi(T) x, VST visit) {
        if (!x)
            return;
        visit(x->data);
        travPre_R(x->lc, visit);
        travPre_R(x->rc, visit);
    }
    template <typename VST> void travPre_I1(BinNodePosi(T) x, VST visit) {
        Stack<BinNodePosi(T)> s;
        if (x)
            s.push(x);
        while (!s.empty()) {
            x = s.pop();
            visit(x->data);
            if (HasRChild(*x))
                s.push(x->rc);
            if (HasLChild(*x))
                s.push(x->lc);
        }
    }
    template <typename VST> void travPre_I2(BinNodePosi(T) x, VST visit) {
        Stack<BinNodePosi(T)> S;
        while (true) {
            visitAlongLeftBranch(x, visit, S);
            if (S.empty())
                break;
            x = S.pop();
        }
    }
    template <typename VST> void visitAlongLeftBranch(BinNodePosi(T) x, VST visit, Stack<BinNodePosi(T)>& S) {
        while (x) {
            visit(x->data);
            S.push(x->rc);
            x = x->lc;
        }
    }

    //中序遍历
    template <typename VST> void travIn_R(BinNodePosi(T) x, VST visit) {
        if (!x)
            return;
        travIn_R(x->lc, visit);
        visit(x->data);
        travIn_R(x->rc, visit);
    }
    template <typename VST> void travIn_I1(BinNodePosi(T) x, VST visit) {
        Stack<BinNodePosi(T)> S;
        while (true) {
            goAlongLeftBranch(x, S);
            if (S.empty())
                break;
            x = S.pop();
            visit(x->data);
            x = x->rc;
        }
    }
    void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
        while (x) {
            S.push(x);
            x = x->lc;
        }
    }
    template <typename VST> void travIn_I2(BinNodePosi(T) x, VST visit) {
        Stack<BinNodePosi(T)> S;
        while (true) {
            if (x) {
                S.push(x);
                x = x->lc;
            } else if (!S.empty()) {
                x = S.pop();
                visit(x->data);
                x = x->rc;
            } else
                break;
        }
    }
    template <typename VST> void travIn_I3(BinNodePosi(T) x, VST visit) {
        bool backtrack = false;
        while (true) {
            //还未到该访问的时机，没有左孩子等价于刚回溯
            if (!backtrack && HasLChild(*x)) {
                x = x->lc;
            } else {
                visit(x->data);
                //寻找后继
                if (HasRChild(*x)) {
                    x = x->rc;
                    backtrack = false;
                } else {
                    //只在回溯的时候调用succ()方法
                    if (!(x = x->succ()))
                        break;
                    backtrack = true;
                }
            }
        }
    }

    //后序遍历
    template <typename VST> void travPost_R(BinNodePosi(T) x, VST visit) {
        if (!x)
            return;
        travPost_R(x->lc, visit);
        travPost_R(x->rc, visit);
        visit(x->data);
    }
    template <typename VST> void travPost_I(BinNodePosi(T) x, VST visit) {
        Stack<BinNodePosi(T)> S;
        if (x)
            S.push(x);
        while (!S.empty()) {
            if (S.top() != x->parent)
                gotoHLVFL(S);
            x = S.pop();
            visit(x->data);
        }
    }
    void gotoHLVFL(Stack<BinNodePosi(T)>& S) {
        while (BinNodePosi(T) x = S.top()) {
            if (HasLChild(*x)) {
                if (HasRChild(*x))
                    S.push(x->rc);
                S.push(x->lc);
            } else
                S.push(x->rc);
        }
        S.pop();
    }

    //层次遍历
    template <typename VST> void travLevel(BinNodePosi(T) x, VST visit) {
        Queue<BinNodePosi(T)> Q;
        Q.enqueue(x);
        while (!Q.empty()) {
            x = Q.dequeue();
            visit(x->data);
            if (HasLChild(*x))
                Q.enqueue(x->lc);
            if (HasRChild(*x))
                Q.enqueue(x->rc);
        }
    }

    //树形打印树结构
    void printTree() {
        if (typeid(T) == typeid(char)) {
            printArray.clear();
            cacuArray();
            //最后一行不打印
            for (int i = 0; i < printArray.size() - 1; ++i)
                cout << printArray[i] << endl;
        }
    }
    void cacuArray() {
        Queue<BinNodePosi(T)> Q;
        Q.enqueue(_root);
        _root->level = 1;
        while (!Q.empty()) {
            BinNodePosi(T) x = Q.dequeue();
            //该行及下一行打印的字符串
            char *s1, *s2;
            if (printArray.size() < 2 * x->level) {
                s1 = new char[256];
                s2 = new char[256];
                memset(s1, 0, 256);
                memset(s2, 0, 256);
                printArray.insert(s1);
                printArray.insert(s2);
            } else {
                s1 = printArray[2 * x->level - 2];
                s2 = printArray[2 * x->level - 1];
            }
            //确定该点打印的位置
            x->position = IsLChild(*x) ? Position(x->parent) - Size(x->rc) - 1 : Position(x->parent) + Size(x->lc) + 1;
            s1[x->position] = x->data;
            //确定左右两侧横线的位置
            int leftCount = x->lc ? 1 + Size(x->lc->rc) : 0;
            int rightCount = x->rc ? 1 + Size(x->rc->lc) : 0;
            for (int i = leftCount == 1 ? 1 : leftCount - 1; i > 0; --i)
                s1[x->position - i] = '-';
            for (int i = rightCount == 1 ? 1 : rightCount - 1; i > 0; --i)
                s1[x->position + i] = '-';
            //打印两行之间的连线
            if (leftCount)
                s2[x->position - leftCount] = '|';
            if (rightCount)
                s2[x->position + rightCount] = '|';
            //将有效字符前面的0置为空
            for (int i = 0; i < x->position + rightCount; ++i) {
                if (!s1[i])
                    s1[i] = ' ';
                if (!s2[i])
                    s2[i] = ' ';
            }
            if (HasLChild(*x)) {
                x->lc->level = x->level + 1;
                Q.enqueue(x->lc);
            }
            if (HasRChild(*x)) {
                x->rc->level = x->level + 1;
                Q.enqueue(x->rc);
            }
        }
    };
};