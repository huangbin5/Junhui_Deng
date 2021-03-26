#include "Graph.hpp"

template <typename Tv, typename Te> struct PrimPU {
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
        if (UNDISCOVERED == g->status(v) && g->priority(v) > g->weight(uk, v)) {
            g->priority(v) = g->weight(uk, v);
            g->parent(v) = uk;
        }
    }
};

template <typename Tv, typename Te> struct DijkstraPU {
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
        if (UNDISCOVERED == g->status(v) && g->priority(v) > g->priority(uk) + g->weight(uk, v)) {
            g->priority(v) = g->priority(uk) + g->weight(uk, v);
            g->parent(v) = uk;
        }
    }
};