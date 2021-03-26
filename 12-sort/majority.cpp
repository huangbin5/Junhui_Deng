#include "../02-vector/vector/Vector.hpp"

template <typename T> bool majority(Vector<T> A, T& maj) {
    maj = majEleCandidate(A);
    return majEleCheck(A, maj);
}

template <typename T> T majEleCandidate(Vector<T> A) {
    T maj;
    for (int c = 0, i = 0; i < A.size(); ++i) {
        if (c)
            maj == A[i] ? ++c : --c;
        else {
            maj = A[i];
            c = 1;
        }
    }
    return maj;
}

template <typename T> bool majEleCheck(Vector<T> A, T maj) {
    int occurrence = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == maj)
            ++occurrence;
    }
    return 2 * occurrence > A.size();
}