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

// 1 2 3 4 5 6 7 8 9 10
void print_non_negative(uint32_t x) {
    static char buf[12];
    int len = sprintf(buf, "%" PRIu32, x);
    print_str(buf, len);
}

void print_non_negative_64(uint64_t x) {
    static char buf[20];
    int len = sprintf(buf, "%" PRIu64, x);
    print_str(buf, len);
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
