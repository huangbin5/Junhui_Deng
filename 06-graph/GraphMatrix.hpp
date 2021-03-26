#include "../02-vector/vector/Vector.hpp"
#include "Graph.hpp"

template <typename Tv> struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent, priority;

    Vertex(const Tv& d = (Tv)0)
        : data(d)
        , inDegree(0)
        , outDegree(0)
        , status(UNDISCOVERED)
        , dTime(-1)
        , fTime(-1)
        , parent(-1)
        , priority(INT_MAX) {}
};

template <typename Te> struct Edge {
    Te data;
    int weight;
    EType type;

    Edge(const Te& d, int w)
        : data(d)
        , weight(w)
        , type(UNDETERMINED) {}
};

template <typename Tv, typename Te> class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;

public:
    GraphMatrix() { Graph<Tv, Te>::n = Graph<Tv, Te>::e = 0; }
    ~GraphMatrix() {
        for (int i = 0; i < Graph<Tv, Te>::n; ++i)
            for (int j = 0; j < Graph<Tv, Te>::n; ++j)
                delete E[i][j];
    }

    //顶点静态操作
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, Graph<Tv, Te>::n); }
    virtual int nextNbr(int i, int j) {
        while ((j > -1) && (!exists(i, --j)))
            ;
        return j;
    }
    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }

    //顶点动态操作
    virtual int insert(const Tv& vertex) {
        for (int i = 0; i < Graph<Tv, Te>::n; ++i)
            E[i].insert(NULL);
        ++Graph<Tv, Te>::n;
        E.insert(Vector<Edge<Te>*>(Graph<Tv, Te>::n, Graph<Tv, Te>::n, (Edge<Te>*)NULL));
        return V.insert(Vertex<Tv>(vertex));
    }
    virtual Tv remove(int i) {
        for (int j = 0; j < Graph<Tv, Te>::n; ++j)
            if (exists(i, j)) {
                delete E[i][j];
                --V[j].inDegree;
            }
        E.remove(i);
        --Graph<Tv, Te>::n;
        for (int j = 0; j < Graph<Tv, Te>::n; ++j)
            if (Edge<Te>* edge = E[j].remove(i)) {
                delete edge;
                --V[j].outDegree;
            }
        Tv data = vertex(i);
        V.remove(i);
        return data;
    }

    //边静态操作
    virtual bool exists(int i, int j) {
        Edge<Te>* ed = E[i][j];
        return (i >= 0) && (i < Graph<Tv, Te>::n) && (j >= 0) && (j < Graph<Tv, Te>::n) && E[i][j] != NULL;
    }
    virtual EType& type(int i, int j) { return E[i][j]->type; }
    virtual Te& edge(int i, int j) { return E[i][j]->data; }
    virtual int& weight(int i, int j) { return E[i][j]->weight; }

    //边动态操作
    virtual void insert(const Te& edge, int w, int i, int j) {
        if (exists(i, j))
            return;
        E[i][j] = new Edge<Te>(edge, w);
        ++Graph<Tv, Te>::e;
        ++V[i].outDegree;
        ++V[j].inDegree;
    }
    virtual Te remove(int i, int j) {
        if (!exists(i, j))
            return (Te)NULL;
        Te data = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;
        --Graph<Tv, Te>::e;
        --V[i].outDegree;
        --V[j].inDegree;
        return data;
    }
};