#include "BinTree.hpp"
#include <iostream>
using namespace std;

template <typename T> struct Print {
    void operator()(T& e) { cout << e << ' '; }
};

int main() {
    BinTree<char>* myTree = new BinTree<char>;
    BinNodePosi(char) i = myTree->insertAsRoot('i');
    BinNodePosi(char) d = myTree->insertAsLC(i, 'd');
    BinNodePosi(char) c = myTree->insertAsLC(d, 'c');
    BinNodePosi(char) a = myTree->insertAsLC(c, 'a');
    BinNodePosi(char) b = myTree->insertAsRC(a, 'b');
    BinNodePosi(char) h = myTree->insertAsRC(d, 'h');
    BinNodePosi(char) f = myTree->insertAsLC(h, 'f');
    BinNodePosi(char) e = myTree->insertAsLC(f, 'e');
    BinNodePosi(char) g = myTree->insertAsRC(f, 'g');
    BinNodePosi(char) l = myTree->insertAsRC(i, 'l');
    BinNodePosi(char) k = myTree->insertAsLC(l, 'k');
    BinNodePosi(char) j = myTree->insertAsLC(k, 'j');
    BinNodePosi(char) n = myTree->insertAsRC(l, 'n');
    BinNodePosi(char) m = myTree->insertAsLC(n, 'm');
    BinNodePosi(char) p = myTree->insertAsRC(n, 'p');
    BinNodePosi(char) o = myTree->insertAsLC(p, 'o');
    cout << "PreTraverse" << endl;
    myTree->travPre_R(myTree->root(), Print<char>());
    puts("");
    myTree->travPre_I1(myTree->root(), Print<char>());
    puts("");
    myTree->travPre_I2(myTree->root(), Print<char>());
    puts("");
    cout << "InTraverse" << endl;
    myTree->travIn_R(myTree->root(), Print<char>());
    puts("");
    myTree->travIn_I1(myTree->root(), Print<char>());
    puts("");
    myTree->travIn_I2(myTree->root(), Print<char>());
    puts("");
    myTree->travIn_I3(myTree->root(), Print<char>());
    puts("");
    cout << "PostTraverse" << endl;
    myTree->travPost_R(myTree->root(), Print<char>());
    puts("");
    myTree->travPost_I(myTree->root(), Print<char>());
    puts("");
    cout << "LevelTraverse" << endl;
    myTree->travLevel(myTree->root(), Print<char>());
    puts("");
    puts("");
    myTree->printTree();
    system("pause");
    return 0;
}