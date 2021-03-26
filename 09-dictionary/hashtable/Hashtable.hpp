#include "../../02-vector/bitmap/Bitmap.hpp"
#include "../Dictionary.hpp"

template <typename K, typename V> class Hashtable : public Dictionary<K, V> {
private:
    Entry<K, V>** ht;
    int M;
    int N;
    Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int prob4Hit(const K& k) {
        int r = hashCode(k) % M;
        while ((ht[r] && k != ht[r]->key) || (!ht[r] && lazilyRemoved(r)))
            r = (r + 1) % M;
        return r;
    }
    int prob4Free(const K& k) {
        int r = hashCode(k) % M;
        while (ht[r])
            r = (r + 1) % M;
        return r;
    }
    void rehash() {
        int old_capacity = M;
        Entry<K, V>** old_ht = ht;
        M *= 2;
        N = 0;
        ht = new Entry<K, V>*[M];
        memset(ht, 0, sizeof(Entry<K, V>*) * M);
        release(lazyRemoval);
        lazyRemoval = new Bitmap(M);
        for (int i = 0; i < old_capacity; ++i)
            if (old_ht[i])
                put(old_ht[i]->key, old_ht[i]->value);
        release(old_ht);
    }

public:
    Hashtable(int c) {
        M = c; //应该选用不大于c的最大素数
        N = 0;
        ht = new Entry<K, V>*[M];
        memset(ht, 0, sizeof(Entry<K, V>*) * M);
        lazyRemoval = new Bitmap(M);
    }
    ~Hashtable() {
        for (int i = 0; i < M; ++i)
            if (ht[i])
                release(ht[i]);
        release(ht);
        release(lazyRemoval);
    }

    int size() const { return N; }

    V* get(K k) {
        int r = prob4Hit(k);
        return ht[r] ? &(ht[r]->value) : NULL;
    }
    bool put(K, V) {
        if (ht[prob4Hit(k)])
            return false;
        int r = prob4Free(k);
        ht[r] = new Entry<K, V>(k, v);
        ++N;
        if (N * 2 > M)
            rehash();
        return true;
    }
    bool remove(K k) {
        int r = prob4Hit(k);
        if (!ht[r])
            return false;
        release(ht[r]);
        ht[r] = NULL;
        markAsRemoved(r);
        --N;
        return true;
    }
};