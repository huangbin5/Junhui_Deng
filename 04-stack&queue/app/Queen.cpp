#include "../stack/Stack.hpp"

int nCheck, nSolu;

struct Queen {
    int x, y;
    Queen(int xx = 0, int yy = 0)
        : x(xx)
        , y(yy){};
    bool operator==(const Queen& q) const { return (x == q.x || y == q.y || x + y == q.x + q.y || x - y == q.x - q.y); }
    bool operator!=(const Queen& q) const { return !(*this == q); }
};

void placeQueen(int N) {
    Stack<Queen> solu;
    Queen q(0, 0);
    do {
        if (solu.size() >= N || q.y >= N) {
            q = solu.pop();
            ++q.y;
        } else {
            while (q.y < N && solu.find(q) >= 0) {
                ++q.y;
                ++nCheck;
            }
            if (q.y < N) {
                solu.push(q);
                if (solu.size() >= N)
                    ++nSolu;
                ++q.x;
                q.y = 0;
            }
        }
    } while (q.x > 0 || q.y < N);
}