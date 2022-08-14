#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IBUFSIZE 20000000
#define OBUFSIZE 10000

char ibuf[IBUFSIZE], obuf[OBUFSIZE];
char *ibufptr = &*ibuf, *obufptr = &*obuf;

// assumes "x y z"
int read_non_negative() {
    ++ibufptr;
    int ans = 0;
    while (*ibufptr >= '0') ans = ans * 10 + *(ibufptr++) - '0';
    return ans;
}

void print_char(char x) {
    *(obufptr++) = x;
}

// 1 2 3 4 5 6 7 8 9 10
void print_non_negative(int x) {
#define PRINT_MID(X, P) print_char((x / P) % 10 + 48)
#define PRINT_TOP(X, P) print_char(x / P + 48)
#define PRINT_BOTTOM(X) print_char(x % 10 + 48)
    if (x < 1000000) {
        if (x < 1000) {
            if (x < 10) {
                print_char(x + 48);
            } else if (x < 100) {
                PRINT_TOP(X, 10);
                PRINT_BOTTOM(X);
            } else {
                PRINT_TOP(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            }
        } else {
            if (x < 10000) {
                PRINT_TOP(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            } else if (x < 100000) {
                PRINT_TOP(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            } else {
                PRINT_TOP(X, 100000);
                PRINT_MID(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            }
        }
    } else {
        if (x < 100000000) {
            if (x < 10000000) {
                PRINT_TOP(X, 1000000);
                PRINT_MID(X, 100000);
                PRINT_MID(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            } else {
                PRINT_TOP(X, 10000000);
                PRINT_MID(X, 1000000);
                PRINT_MID(X, 100000);
                PRINT_MID(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            }
        } else {
            if (x < 1000000000) {
                PRINT_TOP(X, 100000000);
                PRINT_MID(X, 10000000);
                PRINT_MID(X, 1000000);
                PRINT_MID(X, 100000);
                PRINT_MID(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            } else {
                PRINT_TOP(X, 1000000000);
                PRINT_MID(X, 100000000);
                PRINT_MID(X, 10000000);
                PRINT_MID(X, 1000000);
                PRINT_MID(X, 100000);
                PRINT_MID(X, 10000);
                PRINT_MID(X, 1000);
                PRINT_MID(X, 100);
                PRINT_MID(X, 10);
                PRINT_BOTTOM(X);
            }
        }
    }
#undef PRINT_MID
#undef PRINT_TOP
#undef PRINT_BOTTOM
}

void print(int x) {
    if (x < 0)
        print_non_negative(-x);
    else
        print_non_negative(x);
}

void swap_detail(void* p1, void* p2, void* tmp, size_t pSize) {
    memcpy(tmp, p1, pSize), memcpy(p1, p2, pSize), memcpy(p2, tmp, pSize);
}
#define SWAP(a, b)                                                       \
    swap_detail(                                                         \
        &(a), &(b),                                                      \
        (char[(sizeof(a) == sizeof(b)) ? (ptrdiff_t)sizeof(a) : -1]){0}, \
        sizeof(a))

typedef long long ll;

#define GEN_PRINT(NAME, TYPE, SPECIFIER_STR)  \
    int print_generated_##NAME(TYPE x) {      \
        return printf(SPECIFIER_STR "\n", x); \
    }

GEN_PRINT(int, int, "%d")
GEN_PRINT(char, char, "%c")
GEN_PRINT(float, float, "%f")
GEN_PRINT(str, char*, "%s")
GEN_PRINT(ptr, void*, "%p")

#define print_any(X)                            \
    _Generic((X),                               \
            int : print_generated_int,          \
            float : print_generated_float,      \
            char : print_generated_char,        \
            char* : print_generated_str,        \
            default : print_generated_ptr       \
            )(X)

#ifdef DEBUG
    #define debug(X)            \
        do {                    \
            printf("%s: ", #X); \
            print_any(X);       \
        } while (0)
#else
    #define debug(X) 0
#endif

#define N 1000001
#define Q 10

typedef struct {
    int v, next;
} edge;

int n;
int root = -1;

edge tree[2 * N + 1];
int head[N];
int cur_edge = 1;
void add_edge(int u, int v) {
    tree[cur_edge] = (edge){u, head[v]};
    head[v] = cur_edge++;
}

int deg[N];

int d_leaf[N];
int q[N];
int q_l = 0, q_r = -1;

int queries;
int query[Q];
int ans[Q];

int* dp[N];
int dp_len[N];
int depth[N];

void dfs(int u, int p) {
    if (p != -1) depth[u] = depth[p] + 1;
    for (int it = head[u]; it; it = tree[it].next) {
        int v = tree[it].v;
        if (v == p) continue;
        dfs(v, u);
        if (dp_len[u] < dp_len[v]) {
            SWAP(dp_len[u], dp_len[v]);
            SWAP(dp[u], dp[v]);
        }
        int dp_len_v = dp_len[v];
        int dp_len_u = dp_len[u];
        for (int i = 0; i < dp_len_v; ++i) {
            for (int qid = 0; qid < queries; ++qid) {
                int x = query[qid], *a = &ans[qid];
                while (true) {
                    bool stop = true;
                    int j = *a - x - i + 1 > 0 ? *a - x - i + 1 : 0;
                    if (j < dp_len_u && dp[v][i] + dp[u][j] - 2 * depth[u] > *a)
                        ++*a, stop = false;
                    if (stop) break;
                }
            }
        }
        for (int i = 0; i < dp_len_v; ++i)
            if (dp[u][i] < dp[v][i]) dp[u][i] = dp[v][i];
        dp_len[v] = 0;
        free(dp[v]);
        dp[v] = NULL;
    }
    // merge with u
    int i = d_leaf[u];
    int dp_len_u = dp_len[u];
    for (int qid = 0; qid < queries; ++qid) {
        int x = query[qid], *a = &ans[qid];
        while (true) {
            bool stop = true;
            int j = *a - x - i + 1 > 0 ? *a - x - i + 1 : 0;
            if (j < dp_len_u && dp[u][j] - depth[u] > *a) ++*a, stop = false;
            if (stop) break;
        }
    }
    if (dp_len_u <= d_leaf[u])
        dp[u] = realloc(dp[u], (d_leaf[u] + 1) * sizeof(int)),
        dp_len[u] = d_leaf[u] + 1;
    for (int i = dp_len_u; i <= d_leaf[u]; ++i) dp[u][i] = 0;
    if (dp[u][d_leaf[u]] < depth[u]) dp[u][d_leaf[u]] = depth[u];
}

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    n = read_non_negative();
    for (int i = 1; i < n; ++i) {
        int u = read_non_negative() - 1;
        ++deg[i], ++deg[u];
        add_edge(i, u);
        add_edge(u, i);
    }
    for (int i = 0; i < n; ++i)
        if (deg[i] > 1) {
            root = i;
            d_leaf[i] = -1;
        } else {
            d_leaf[i] = 0;
            q[++q_r] = i;
        }
    assert(root != -1);
    while (q_l <= q_r) {
        int u = q[q_l++];
        int d_leaf_u = d_leaf[u];
        for (int it = head[u]; it; it = tree[it].next) {
            int v = tree[it].v;
            if (d_leaf[v] == -1) {
                d_leaf[v] = d_leaf_u + 1;
                q[++q_r] = v;
            }
        }
    }
    queries = read_non_negative();
    for (int i = 0; i < queries; ++i) query[i] = read_non_negative();
    dfs(root, -1);
    for (int i = 0; i < queries; ++i)
        print_non_negative(ans[i]), print_char(" \n"[i == queries - 1]);
    fwrite(obuf, 1, obufptr - obuf, stdout);
}
