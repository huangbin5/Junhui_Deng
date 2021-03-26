#include "../02-vector/vector/Vector.hpp"

template <typename T> T quickSelect(Vector<T> A, Rank k) {
    for (Rank lo = 0, hi = A.size() - 1; lo < hi;) {
        Rank i = lo, j = hi;
        T pivot = A[lo];
        while (i < j) {
            while (i < j && pivot <= A[j])
                --j;
            A[i] = A[j];
            while (i < j && pivot >= A[i])
                ++i;
            A[j] = A[i];
        }
        A[i] = pivot;
        if (k <= i)
            hi = i - 1;
        if (i <= k)
            lo = i + 1;
    }
    return A[k];
}