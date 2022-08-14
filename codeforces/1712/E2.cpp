#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <inttypes.h>
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

void print_str(const char* const c, size_t len) {
    memcpy(obufptr, c, len);
    obufptr += len;
}

#define PRINT_MID(X, P) print_char(((X) / (P)) % 10 + 48)
#define PRINT_TOP(X, P) print_char((X) / (P) + 48)
#define PRINT_BOTTOM(X) print_char((X) % 10 + 48)

#define MID_10(X) PRINT_MID(X, 10)
#define MID_100(X)     \
    PRINT_MID(X, 100); \
    MID_10(X);
#define MID_1000(X)     \
    PRINT_MID(X, 1000); \
    MID_100(X);
#define MID_10000(X)     \
    PRINT_MID(X, 10000); \
    MID_1000(X);
#define MID_100000(X)     \
    PRINT_MID(X, 100000); \
    MID_10000(X);
#define MID_1000000(X)     \
    PRINT_MID(X, 1000000); \
    MID_100000(X);
#define MID_10000000(X)     \
    PRINT_MID(X, 10000000); \
    MID_1000000(X);
#define MID_100000000(X)     \
    PRINT_MID(X, 100000000); \
    MID_10000000(X);
#define MID_1000000000(X)     \
    PRINT_MID(X, 1000000000); \
    MID_100000000(X);
#define MID_10000000000(X)     \
    PRINT_MID(X, 10000000000); \
    MID_1000000000(X);
#define MID_100000000000(X)     \
    PRINT_MID(X, 100000000000); \
    MID_10000000000(X);
#define MID_1000000000000(X)     \
    PRINT_MID(X, 1000000000000); \
    MID_100000000000(X);
#define MID_10000000000000(X)     \
    PRINT_MID(X, 10000000000000); \
    MID_1000000000000(X);
#define MID_100000000000000(X)     \
    PRINT_MID(X, 100000000000000); \
    MID_10000000000000(X);
#define MID_1000000000000000(X)     \
    PRINT_MID(X, 1000000000000000); \
    MID_100000000000000(X);
#define MID_10000000000000000(X)     \
    PRINT_MID(X, 10000000000000000); \
    MID_1000000000000000(X);
#define MID_100000000000000000(X)     \
    PRINT_MID(X, 100000000000000000); \
    MID_10000000000000000(X);
#define MID_1000000000000000000(X)     \
    PRINT_MID(X, 1000000000000000000); \
    MID_100000000000000000(X);
#define MID_10000000000000000000(X)     \
    PRINT_MID(X, 10000000000000000000); \
    MID_1000000000000000000(X);

#define PRINT_ALL(X, P)      \
    PRINT_TOP(X, 10ULL * P); \
    MID_##P(X);              \
    PRINT_BOTTOM(X);

// 1 2 3 4 5 6 7 8 9 10
void print_non_negative(uint32_t x) {
    if (x < 1000000) {
        if (x < 1000) {
            if (x < 10) {
                print_char(x + 48);
            } else if (x < 100) {
                PRINT_TOP(x, 10);
                PRINT_BOTTOM(x);
            } else {
                PRINT_ALL(x, 10);
            }
        } else {
            if (x < 10000) {
                PRINT_ALL(x, 100);
            } else if (x < 100000) {
                PRINT_ALL(x, 1000);
            } else {
                PRINT_ALL(x, 10000);
            }
        }
    } else {
        if (x < 100000000) {
            if (x < 10000000) {
                PRINT_ALL(x, 100000);
            } else {
                PRINT_ALL(x, 1000000);
            }
        } else {
            if (x < 1000000000) {
                PRINT_ALL(x, 10000000);
            } else {
                PRINT_ALL(x, 100000000);
            }
        }
    }
}

void print_non_negative_64(uint64_t x) {
    if (x < 10000000000) {
        if (x < 1000000) {
            if (x < 1000) {
                if (x < 10) {
                    print_char(x + 48);
                } else if (x < 100) {
                    PRINT_TOP(x, 10);
                    PRINT_BOTTOM(x);
                } else {
                    PRINT_ALL(x, 10);
                }
            } else {
                if (x < 10000) {
                    PRINT_ALL(x, 100);
                } else if (x < 100000) {
                    PRINT_ALL(x, 1000);
                } else {
                    PRINT_ALL(x, 10000);
                }
            }
        } else {
            if (x < 100000000) {
                if (x < 10000000) {
                    PRINT_ALL(x, 100000);
                } else {
                    PRINT_ALL(x, 1000000);
                }
            } else {
                if (x < 1000000000) {
                    PRINT_ALL(x, 10000000);
                } else {
                    PRINT_ALL(x, 100000000);
                }
            }
        }
    } else {
        if (x < 10000000000000000) {
            if (x < 10000000000000) {
                if (x < 100000000000) {
                    PRINT_ALL(x, 1000000000);
                } else if (x < 1000000000000) {
                    PRINT_ALL(x, 10000000000);
                } else {
                    PRINT_ALL(x, 100000000000);
                }
            } else {
                if (x < 100000000000000) {
                    PRINT_ALL(x, 1000000000000);
                } else if (x < 1000000000000000) {
                    PRINT_ALL(x, 10000000000000);
                } else {
                    PRINT_ALL(x, 100000000000000);
                }
            }
        } else {
            if (x < 1000000000000000000) {
                if (x < 100000000000000000) {
                    PRINT_ALL(x, 1000000000000000);
                } else {
                    PRINT_ALL(x, 10000000000000000);
                }
            } else {
                PRINT_ALL(x, 100000000000000000);
            }
        }
    }
}

#undef PRINT_MID
#undef PRINT_TOP
#undef PRINT_BOTTOM

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
