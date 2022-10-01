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
#define MOD 998244353

char a[N + 1][N + 1];
int dp[N + 1][N + 1];

void solve() {
    int n = read_u32(), k = read_u32();
    for (int i = 0; i < n; ++i) load_str_n(a[i], n);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j) dp[i][j] = 0;

    for (int i = 1; i < k; ++i)
        for (int j = 1; j <= k - i; ++j) dp[i][n - j + 1] = i, dp[n - i + 1][j] = j;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = max(
                max(dp[i][j], dp[i][j - 1]),
                max(dp[i - 1][j], dp[i - 1][j - 1] + (a[i - 1][j - 1] == '0')));
    if (dp[n][n] >= k) {
        no();
        return;
    }
    yes();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            print_char('0' + (dp[i + 1][j + 1] > dp[i][j]));
        print_char('\n');
    }
}

int main() {
    init();
    int t = read_u32();
    while (t--) solve();
}

