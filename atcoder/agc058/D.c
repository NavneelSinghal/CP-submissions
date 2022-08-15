#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define IBUFSIZE 10000
#define OBUFSIZE 10000

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

#define MOD 998244353

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int binexp(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = mul(ans, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

int inv(int a) {
    assert(a);
    return binexp(a, MOD - 2);
}

#define N 1000000

int fact[3 * N + 1], ifact[3 * N + 1];

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= 3 * N; ++i) fact[i] = mul(fact[i - 1], i);
    ifact[3 * N] = inv(fact[3 * N]);
    for (int i = 3 * N - 1; i >= 0; --i) ifact[i] = mul(ifact[i + 1], i + 1);
}

int C(int a, int b, int c, int d) {
    return mul(fact[a + b + c + d],
               mul(mul(ifact[a], ifact[b]), mul(ifact[c], ifact[d])));
}

int coeff(int a, int b, int c) {
    int x = a;
    if (b < x) x = b;
    if (c < x) x = c;
    int pw = 1, ans = 0;
    for (int i = 0; i <= x; ++i) {
        ans = add(ans, mul(pw, C(a - i, b - i, c - i, i)));
        pw = mul(pw, MOD - 2);
    }
    return ans;
}

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    init_fact();
    int a = read_u32(), b = read_u32(), c = read_u32();
    int ans = sub(
        add(add(coeff(a - 1, b, c), coeff(a, b - 1, c)), coeff(a, b, c - 1)),
        mul(3, coeff(a - 1, b - 1, c - 1)));
    print_u32(ans);
    print_char('\n');
    fwrite(obuf, 1, obufptr - obuf, stdout);
}
