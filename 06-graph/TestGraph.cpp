#include "GraphMatrix.hpp"
#include <iostream>
using namespace std;

int main() {
    GraphMatrix<char, int> g;
    g.insert('S');
    g.insert('A');
    g.insert('B');
    g.insert('C');
    g.insert('D');
    g.insert('E');
    g.insert('F');
    g.insert('G');
    g.insert(1, 1, 0, 1);
    g.insert(1, 1, 0, 3);
    g.insert(1, 1, 0, 4);
    g.insert(1, 1, 1, 3);
    g.insert(1, 1, 1, 5);
    g.insert(1, 1, 3, 2);
    g.insert(1, 1, 4, 2);
    g.insert(1, 1, 5, 6);
    g.insert(1, 1, 5, 7);
    g.insert(1, 1, 7, 2);
    g.insert(1, 1, 7, 6);
    g.bfs(0);

    system("pause");
    return 0;
}