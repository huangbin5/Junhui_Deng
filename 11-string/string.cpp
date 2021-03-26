#include <algorithm>
#include <cstring>
using namespace std;

/**
 * 蛮力匹配
 */
int match_bf1(char* p, char* t) {
    size_t n = strlen(t), i = 0;
    size_t m = strlen(p), j = 0;
    while (j < m && i < n) {
        if (t[i] == p[j]) {
            ++i;
            ++j;
        } else {
            i -= j - 1;
            j = 0;
        }
    }
    return i - j;
}

int match_bf2(char* p, char* t) {
    size_t n = strlen(t), i;
    size_t m = strlen(p), j;
    for (i = 0; i < n - m + 1; ++i) {
        for (j = 0; j < m; ++j) {
            if (t[i + j] != p[j])
                break;
            if (j >= m)
                break;
        }
    }
    return i;
}

/**
 * KMP算法
 */
int* buildNext(char* p) {
    size_t m = strlen(p), j = 0;
    int* next = new int[m];
    int t = next[0] = -1;
    while (j < m - 1) {
        if (t < 0 || p[j] == p[t]) {
            ++t;
            ++j;
            next[j] = t;
        } else
            t = next[t];
    }
    return next;
}

int* buildNext_adv(char* p) {
    size_t m = strlen(p), j = 0;
    int* next = new int[m];
    int t = next[0] = -1;
    while (j < m - 1) {
        if (t < 0 || p[j] == p[t]) {
            ++j;
            ++t;
            next[j] = p[j] == p[t] ? next[t] : t;
        } else
            t = next[t];
    }
    return next;
}

int match_kmp(char* p, char* t) {
    int* next = buildNext(p);
    int n = strlen(t), i = 0;
    int m = strlen(p), j = 0;
    while (i < n && j < m) {
        if (j < 0 || t[i] == p[j]) {
            ++i;
            ++j;
        } else
            j = next[j];
    }
    delete[] next;
    return i - j;
}

/**
 * BM算法
 */
int* buildBC(char* p) {
    int* bc = new int[256];
    for (int j = 0; j < 256; ++j)
        bc[j] = -1;
    for (int m = strlen(p), j = 0; j < m; ++j) {
        bc[p[j]] = j;
    }
    return bc;
}

int* buildSS(char* p) {
    int m = strlen(p);
    int* ss = new int[m];
    ss[m - 1] = m;
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; --j) {
        if (lo < j && ss[m - hi + j - 1] <= j - lo)
            ss[j] = ss[m - hi + j - 1];
        else {
            hi = j;
            lo = min(lo, hi);
            while (lo >= 0 && p[lo] == p[m - hi + lo - 1])
                --lo;
            ss[j] = hi - lo;
        }
    }
    return ss;
}

int* buildGS(char* p) {
    int* ss = buildSS(p);
    int m = strlen(p);
    int* gs = new int[m];
    for (int j = 0; j < m; ++j)
        gs[j] = m;
    for (int i = 0, j = m - 1; j >= 0; --j) {
        if (j + 1 == ss[j])
            while (i < m - j - 1)
                gs[i++] = m - j - 1;
    }
    for (int j = 0; j < m - 1; ++j)
        gs[m - ss[j] - 1] = m - j - 1;
    delete[] ss;
    return gs;
}

int match_bm(char* p, char* t) {
    int* bc = buildBC(p);
    int* gs = buildGS(p);
    int i = 0;
    while (strlen(t) >= i + strlen(p)) {
        int j = strlen(p) - 1;
        while (p[j] == t[i + j])
            if (--j < 0)
                break;
        if (j < 0)
            break;
        else
            i += max(gs[j], j - bc[t[i + j]]);
    }
    delete[] bc;
    delete[] gs;
    return i;
}