#include "../04-stack&queue/queue/Queue.hpp"
#include "../04-stack&queue/stack/Stack.hpp"
#include <limits.h>
using namespace std;
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te> class Graph {
private:
    //对所有的顶点和边复位
    void reset() {
        for (int i = 0; i < n; ++i) {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j < n; ++j)
                if (exists(i, j))
                    type(i, j) = UNDETERMINED;
        }
    }

    //以下都是连通域内的算法
    void BFS(int v, int& clock) {
        Queue<int> Q;
        status(v) = DISCOVERED;
        Q.enqueue(v);
        while (!Q.empty()) {
            v = Q.dequeue();
            dTime(v) = ++clock;
            cout << vertex(v) << endl;
            for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
                if (UNDISCOVERED == status(u)) {
                    status(u) = DISCOVERED;
                    Q.enqueue(u);
                    type(v, u) = TREE;
                    parent(u) = v;
                } else
                    type(v, u) = CROSS;
            status(v) = VISITED;
        }
    }
    void DFS(int v, int& clock) {
        dTime(v) = ++clock;
        status(v) = DISCOVERED;
        for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
            switch (status(u)) {
            case UNDISCOVERED:
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                break;
            default:
                type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
            }
        }
        status(v) = VISITED;
        fTime(v) = ++clock;
    }
    void BCC(int, int&, Stack<int>&);
    bool TSort(int v, int& clock, Stack<Tv>* S) {
        dTime(v) = ++clock;
        status(v) = DISCOVERED;
        for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
            switch (status(u)) {
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if (!TSort(u, clock, S))
                    return false;
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                return false;
            default:
                type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
            }
        }
        status(v) = VISITED;
        S->push(vertex(v));
        return true;
    }
    template <typename PU> void PFS(int s, PU prioUpdater) {
        priority(s) = 0;
        status(s) = VISITED;
        parent(s) = -1;
        for (;;) {
            for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
                prioUpdater(this, s, w);
            for (int shortest = INT_MAX, w = 0; w < n; ++w)
                if (UNDISCOVERED == status(w) && priority(w) < shortest) {
                    shortest = priority(w);
                    s = w;
                }
            if (VISITED == status(s))
                break;
            status(s) = VISITED;
            type(parent(s), s) = TREE;
        }
    }

public:
    //顶点
    int n;
    virtual int insert(const Tv&) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv& vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int, int) = 0;
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0;

    //边
    int e;
    virtual bool exists(int, int) = 0;
    virtual void insert(const Te&, int, int, int) = 0;
    virtual Te remove(int, int) = 0;
    virtual EType& type(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int, int) = 0;

    //算法
    void bfs(int s) {
        reset();
        int clock = 0, v = s;
        do
            if (status(v) == UNDISCOVERED)
                BFS(v, clock);
        while (s != (v = (++v % n)));
    }
    void dfs(int s) {
        reset();
        int clock = 0, v = s;
        do
            if (status(v) == UNDISCOVERED)
                DFS(v, clock);
        while (s != (v = (++v % n)));
    }
    void bcc(int);
    Stack<Tv>* tSort(int s) {
        reset();
        int clock = 0, v = s;
        Stack<Tv>* S = new Stack<Tv>;
        do {
            if (UNDISCOVERED == status(v))
                if (!TSort(v, clock, S)) {
                    while (!S->empty())
                        S->pop();
                    break;
                }
        } while (s != (v = (++v % n)));
        return S;
    }
    void prim(int);
    void dijkstra(int);
    template <typename PU> void pfs(int s, PU prioUpdater) {
        reset();
        int v = s;
        do
            if (UNDISCOVERED == status(v))
                PFS(v, prioUpdater);
        while (s != (v = (++v % n)));
    }
};