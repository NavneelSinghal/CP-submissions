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

#define IBUFSIZE 5000000
#define OBUFSIZE 5000000

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

#define N_FACTORIAL 200000
#define MOD 998244353

typedef struct {
    int value;
} mint;

mint construct_mint(int a) {
    return (mint){a % MOD};
}

mint add(mint a, mint b) {
    mint ans = {a.value + b.value};
    if (ans.value >= MOD) ans.value -= MOD;
    return ans;
}

mint subtract(mint a, mint b) {
    mint ans = {a.value - b.value};
    if (ans.value < 0) ans.value += MOD;
    return ans;
}

mint multiply(mint a, mint b) {
    return (mint){INT64_C(1) * a.value * b.value % MOD};
}

mint power(mint a, int p) {
    mint ans = {1};
    while (p) {
        if (p & 1) ans = multiply(ans, a);

        if (p >>= 1) a = multiply(a, a);
    }
    return ans;
}

mint inverse(mint a) {
    assert(a.value != 0);
    return power(a, MOD - 2);
}

mint divide(mint a, mint b) {
    return multiply(a, inverse(b));
}

mint fact[N_FACTORIAL + 1], ifact[N_FACTORIAL + 1];

void precompute() {
    fact[0] = (mint){1};
    for (int i = 1; i <= N_FACTORIAL; ++i)
        fact[i] = multiply(fact[i - 1], (mint){i});
    ifact[N_FACTORIAL] = inverse(fact[N_FACTORIAL]);
    for (int i = N_FACTORIAL - 1; i >= 0; --i)
        ifact[i] = multiply(ifact[i + 1], (mint){i + 1});
}

mint C(int n, int r) {
    if (r < 0 || r > n) return (mint){0};
    return multiply(fact[n], multiply(ifact[r], ifact[n - r]));
}

#define N 100000
int a[N];

mint ways(int n, int m) {
    return multiply(fact[n + m], multiply(ifact[n], ifact[m]));
}

void solve() {
    int n = read_u32();
    for (int i = 0; i < n; ++i) a[i] = read_u32();
    mint ans = {1};
    int l = 0, r = n - 1;
    while (l <= r) {
        int x = l;
        while (x <= r && a[x] == 0) ++x;
        if (x > r) {
            ans = multiply(ans, power((mint){2}, r - l));
            break;
        }
        int y = r;
        while (y >= l && a[y] == 0) --y;
        if (x > l && y < r) {
            ans = multiply(ans, ways(x - l, r - y));
            l = x, r = y;
        } else if (x == y) {
            break;
        } else {
            int64_t sum_left = a[x], sum_right = a[y];
            while (x + 1 < y && sum_left != sum_right)
                if (sum_left < sum_right)
                    sum_left += a[++x];
                else
                    sum_right += a[--y];
            if (sum_left != sum_right) {
                break;
            } else {
                l = ++x, r = --y;
                while (x <= r && a[x] == 0) ++x;
                if (x > r) {
                    ans = multiply(ans, power((mint){2}, r - l + 2));
                    break;
                }
                while (y >= l && a[y] == 0) --y;
                ans = multiply(ans, ways(x - l + 1, r - y + 1));
                l = x, r = y;
            }
        }
    }
    print_u32(ans.value);
    print_char('\n');
}

int main() {
    init();
    precompute();
    int t = read_u32();
    while (t--) solve();
}

