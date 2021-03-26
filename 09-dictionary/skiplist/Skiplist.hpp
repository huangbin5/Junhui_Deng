#include "../../03-list/List.hpp"
#include "../Dictionary.hpp"
#include "QuadList.hpp"

template <typename K, typename V> class Skiplist : public Dictionary<K, V>, public List<QuadList<Entry<K, V>>*> {
protected:
    bool skipSearch(ListNode<QuadList<Entry<K, V>>*>*& qlist, QuadListNode<Entry<K, V>>*& p, K& k) {
        for (;;) {
            while (p->succ && p->entry.key <= k)
                p = p->succ;
            p = p->pred;
            if (p->pred && k == p->entry.key)
                return true;
            qlist = qlist->succ;
            if (!qlist)
                return false;
            p = p->pred ? p->below : qlist->data->first();
        }
    }

public:
    int size() const { return empty() ? 0 : last()->data->size(); }
    int level() { return List::size(); }

    V* get(K k) {
        if (empty())
            return NULL;
        ListNode<QuadList<Entry<K, V>>*>* qlist = first();
        QuadListNode<Entry<K, V>>* p = qlist->data->first();
        return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL;
    }
    bool put(K, V) {
        Entry<K, V> e = Entry<K, V>(k, v);
        if (empty())
            insertAsFirst(new QuadList<Entry<K, V>>);
        ListNode<QuadList<Entry<K, V>>*> qlist = first();
        QuadListNode<Entry<K, V>>* p = qlist->data->first();
        if (skipSearch(qlist, p, k))
            while (p->below)
                p = p->below;
        qlist = last();
        QuadListNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);
        while (rand() & 1) {
            while (qlist->data->valid(p) && !p->above)
                p = p->pred;
            if (!qlist->data->valid(p)) {
                if (qlist == first())
                    insertAsFirst(new QuadList<Entry<K, V>>);
                p = qlist->pred->data->firsr()->pred;
            } else
                p = p->above;
            qlist = qlist->pred;
            b = qlist->data->insertAfterAbove(e, p, b);
        }
        return true;
    }
    bool remove(K k) {
        if (empty())
            return false;
        ListNode<QuadList<Entry<K, V>>*>* qlist = first();
        QuadListNode<Entry<K, V>>* p = qlist->data->first();
        if (!skipSearch(qlist, p, k))
            return false;
        do {
            QuadListNode<Entry<K, V>>* lower = p->below;
            qlist->data->remove(p);
            p = lower;
            qlist = qlist->succ;
        } while (qlist->succ);
        while (!empty() && first()->data->empty())
            List::remove(first());
        return true;
    }
};