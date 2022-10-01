#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IBUFSIZE 50000000
#define OBUFSIZE 50000000

char ibuf[IBUFSIZE], obuf[OBUFSIZE];
char *ibufptr = &*ibuf, *obufptr = &*obuf;

void print_char(char x) {
    *(obufptr++) = x;
}

void print_str(const char* const c, size_t len) {
    memcpy(obufptr, c, len);
    obufptr += len;
}

void print(const char* const c) {
    print_str(c, strlen(c));
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
    int##X##_t read_i##X() {                                         \
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

void flush() {
    fwrite(obuf, 1, obufptr - obuf, stdout);
}

void init() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    atexit(flush);
}

void no() {
    print_str("NO\n", 3);
}

void yes() {
    print_str("YES\n", 4);
}

int max(int a, int b) {
    return a < b ? b : a;
}

#define N 1000
int degree[N], color[N], colors, cur[N];
bool visited[N];

void solve() {
    int n;
    scanf("%d", &n);
    colors = 0;
    memset(visited, 0, n * sizeof(bool));
    for (int i = 0; i < n; ++i) scanf("%d", &degree[i]);
    while (true) {
        int u = -1;
        for (int i = 0; i < n; ++i)
            if (!visited[i] && (u == -1 || degree[i] > degree[u])) u = i;
        if (u == -1) break;
        int sz = 0;
        cur[sz++] = u;
        int deg = degree[u];
        int old = -1;
        while (deg--) {
            printf("? %d\n", u + 1);
            fflush(stdout);
            int v;
            scanf("%d", &v);
            --v;
            if (visited[v]) {
                old = v;
                break;
            } else {
                cur[sz++] = v;
            }
        }
        int col = old == -1 ? ++colors : color[old];
        for (int i = 0; i < sz; ++i) {
            color[cur[i]] = col;
            visited[cur[i]] = true;
        }
    }
    printf("! ");
    for (int i = 0; i < n; ++i) printf("%d%c", color[i], " \n"[i == n - 1]);
    fflush(stdout);
}

int main() {
    // init();
    // int t = read_u32();
    int t;
    scanf("%d", &t);
    while (t--) solve();
}

