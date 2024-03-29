#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IBUFSIZE 5000000
#define OBUFSIZE 5000000

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
void print_non_negative(uint32_t x) {
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

void print_non_negative_64(uint64_t x) {
    if (x < 10)
        print_char(x + 48);
    else {
        print_non_negative_64(x / 10);
        print_char(x % 10 + 48);
    }
}

#define GEN_PRINT(NAME, TYPE, SPECIFIER_STR)  \
    int print_generated_##NAME(TYPE x) {      \
        return printf(SPECIFIER_STR "\n", x); \
    }

GEN_PRINT(int, int, "%d")
GEN_PRINT(char, char, "%c")
GEN_PRINT(float, float, "%f")
GEN_PRINT(str, char*, "%s")
GEN_PRINT(ptr, void*, "%p")

#define print_any(X) \
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

typedef long long ll;

#define N 200000
#define T 100000

ll a[N + 1];
void add(int i, int v) {
    for (++i; i <= N + 1; i += i & -i) a[i - 1] += v;
}
ll sum(int i) {
    ll ans = 0;
    for (; i; i -= i & -i) ans += a[i - 1];
    return ans;
}

typedef struct {
    int r, i, next;
} query;
int cur_query = 1;
query queries[T + N + 1];
int head[N];
ll ans[T];
int cnt[N + 1];

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    int t = read_non_negative();
    for (int i = 0; i < t; ++i) {
        int l = read_non_negative() - 1;
        int r = read_non_negative();
        // add l, r, i
        queries[cur_query] = (query){r, i, head[l]};
        head[l] = cur_query++;
        int x1 = r / 6 - l / 3;
        int x2 = r / 15 - l / 6;
        ans[i] = 1LL * (r - l) * (r - l - 1) * (r - l - 2) / 6 -
                 (x1 > 0 ? x1 : 0) - (x2 > 0 ? x2 : 0);
    }
    for (int l = N - 1; l >= 0; --l) {
        for (int it = head[l]; it;) {
            query q = queries[it];
            int r = q.r, i = q.i;
            it = q.next;
            ans[i] -= sum(r + 1);
        }
        if (l)
            for (int j = 2 * l; j <= N; j += l) add(j, cnt[j]++);
    }
    for (int i = 0; i < t; ++i) print_non_negative_64(ans[i]), print_char('\n');
    fwrite(obuf, 1, obufptr - obuf, stdout);
}
