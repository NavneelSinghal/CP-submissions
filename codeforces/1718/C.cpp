#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <inttypes.h>
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

typedef int64_t ll;

#define N 200000

int total_primes;
int primes[6], complement[6], size[6];

void factorize(int n) {
    int n_ = n;
    total_primes = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            primes[total_primes++] = i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) primes[total_primes++] = n;
    for (int i = 0; i < total_primes; ++i) {
        complement[i] = n_ / primes[i];
        int p = 1;
        while (p < complement[i]) p <<= 1;
        size[i] = p;
    }
}

ll max(ll a, ll b) {
    return a < b ? b : a;
}

ll t[6][4 * N];

void add(ll* tree, int i, int x, int s) {
    i += s;
    tree[i] += x;
    while (i > 1) {
        i >>= 1;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

void build(ll* tree, int s) {
    for (int i = s - 1; i > 0; --i) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
}

ll query(ll* tree) {
    return tree[1];
}

ll solve() {
    ll ans = 0;
    for (int ptr = 0; ptr < total_primes; ++ptr)
        ans = max(ans, complement[ptr] * query(t[ptr]));
    return ans;
}

int a[N];

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    int tests = read_u32();
    while (tests--) {
        int n = read_u32();
        int q = read_u32();
        factorize(n);
        for (int i = 0; i < n; ++i) a[i] = read_u32();
        for (int ptr = 0; ptr < total_primes; ++ptr) {
            const int skip = complement[ptr];
            const int p2 = size[ptr];
            memset(t[ptr], 0, sizeof(ll) * 2 * size[ptr]);
            for (int start = 0; start < n; start += skip)
                for (int i = 0; i < skip; ++i) t[ptr][p2 + i] += a[start + i];
            build(t[ptr], p2);
        }
        print_u64(solve());
        print_char('\n');
        while (q--) {
            int I = read_u32() - 1;
            int A = read_u32();
            int diff = A - a[I];
            a[I] = A;
            for (int ptr = 0; ptr < total_primes; ++ptr)
                add(t[ptr], I % complement[ptr], diff, size[ptr]);
            print_u64(solve());
            print_char('\n');
        }
    }
    fwrite(obuf, 1, obufptr - obuf, stdout);
}
