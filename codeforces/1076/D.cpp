#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define IBUFSIZE 10000000
#define OBUFSIZE 10000000

char ibuf[IBUFSIZE], obuf[OBUFSIZE];
char *ibufptr = &*ibuf, *obufptr = &*obuf;

void print_char(char x) {
    *(obufptr++) = x;
}

void print_str(const char* const c, size_t len) {
    memcpy(obufptr, c, len);
    obufptr += len;
}

#define PRINT_UNSIGNED(X)            \
    void print_u##X(uint##X##_t x) { \
        if (x < 10)                  \
            print_char(x + 48);      \
        else {                       \
            print_u##X(x / 10);      \
            print_char(x % 10 + 48); \
        }                            \
    }

#define unlikely(x) __builtin_expect(!!(x), 0)
#define PRINT_SIGNED(X)                                        \
    void print_i##X(int##X##_t x) {                            \
        static char buf[100];                                  \
        if (unlikely(x == INT##X##_MIN)) {                     \
            int len = sprintf(buf, "%" PRIi##X, INT##X##_MIN); \
            print_str(buf, len);                               \
        } else if (x < 0) {                                    \
            print_char('-');                                   \
            print_u##X(-x);                                    \
        } else {                                               \
            print_u##X(x);                                     \
        }                                                      \
    }

PRINT_UNSIGNED(32);
PRINT_UNSIGNED(64);
PRINT_SIGNED(32);
PRINT_SIGNED(64);

void skip_char() {
    ++ibufptr;
}

// can do skip_spaces instead of skip_char for this purpose, but it will be
// slower

// assumes "x y z"
#define READ_UNSIGNED(X)                                             \
    uint##X##_t read_u##X() {                                        \
        skip_char();                                                 \
        uint##X##_t ans = 0;                                         \
        while (*ibufptr >= '0') ans = ans * 10 + *(ibufptr++) - '0'; \
        return ans;                                                  \
    }
#define READ_SIGNED(X)                                               \
    uint##X##_t read_i##X() {                                        \
        skip_char();                                                 \
        int##X##_t ans = 0, sign = 1;                                \
        if (*ibufptr == '-') sign = -1, ++ibufptr;                   \
        while (*ibufptr >= '0') ans = ans * 10 + *(ibufptr++) - '0'; \
        return sign * ans;                                           \
    }

READ_UNSIGNED(32);
READ_UNSIGNED(64);
READ_SIGNED(32);
READ_SIGNED(64);

void load_str(char* s) {
    skip_char();
    while (*ibufptr != ' ' && *ibufptr != '\n') *(s++) = *(ibufptr++);
}

void load_str_n(char* s, int n) {
    skip_char();
    for (int i = 0; i < n; ++i) *(s++) = *(ibufptr++);
}

typedef int64_t ll;
#define N 300003

typedef struct {
    ll weight;
    int from, to, index, next;
} edge;

edge edges[2 * N], par[N];
int total_edges = 1;
int head[N], deg[N];
ll d[N];
bool used_edge[N + 1];
int total_used_edges = 0;

void add_edge(int from, int to, ll weight, int index) {
    edges[total_edges] = (edge){weight, from, to, index, head[from]};
    head[from] = total_edges++;
}

typedef struct {
    ll key;
    int value;
} node;

node pq[4 * N];
int pq_size = 0;

void push(node nd) {
    int i = pq_size++;
    pq[i] = nd;
    while (i > 0 && pq[(i - 1) / 2].key > pq[i].key) {
        nd = pq[i];
        pq[i] = pq[(i - 1) / 2];
        pq[(i - 1) / 2] = nd;
    }
}

bool empty() {
    return pq_size == 0;
}

node pop() {
    // assert(!empty());
    node ans = pq[0];
    pq[0] = pq[--pq_size];
    int i = 0;
    while (2 * i + 1 < pq_size) {
        int c = 2 * i + 1;
        if (c + 1 < pq_size && pq[c].key > pq[c + 1].key) ++c;
        if (pq[c].key < pq[i].key) {
            node nd = pq[c];
            pq[c] = pq[i];
            pq[i] = nd;
            i = c;
        } else {
            break;
        }
    }
    return ans;
}

int stk[N];
int stk_size = 0;

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    int n = read_u32();
    int m = read_u32();
    int k = read_u32();
    for (int i = 0; i < m; ++i) {
        int u = read_u32() - 1;
        int v = read_u32() - 1;
        ll w = read_u32();
        add_edge(u, v, w, i + 1);
        add_edge(v, u, w, i + 1);
    }
    // dijkstra
    memset(d, 0x3f, n * sizeof(ll));
    d[0] = 0;
    push((node){d[0], 0});
    while (!empty()) {
        node nd = pop();
        int u = nd.value;
        ll d_u = nd.key;
        if (d[u] != d_u) continue;
        for (int x = head[u]; x; x = edges[x].next) {
            int v = edges[x].to;
            ll w = edges[x].weight;
            if (d[v] > d_u + w) {
                d[v] = d_u + w;
                par[v] = edges[x];
                push((node){d[v], v});
            }
        }
    }
    for (int i = 0; i < n; ++i)
        if (par[i].index) {
            ++deg[par[i].from];
            used_edge[par[i].index] = true;
            ++total_used_edges;
        }
    for (int i = 0; i < n; ++i)
        if (deg[i] == 0) stk[stk_size++] = i;
    while (total_used_edges > k) {
        int u = stk[--stk_size];
        edge p = par[u];
        int v = p.from;
        --deg[v];
        --total_used_edges;
        used_edge[p.index] = false;
        if (deg[v] == 0) stk[stk_size++] = v;
    }
    print_u32(total_used_edges), print_char('\n');
    for (int i = 1; i <= m; ++i)
        if (used_edge[i]) print_u32(i), print_char(' ');
    print_char('\n');
    fwrite(obuf, 1, obufptr - obuf, stdout);
}

