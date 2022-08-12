#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    static int a[500000];
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int mask = 1; mask < n; mask <<= 1)
        for (int i = 0; i < n; ++i)
            if (i & mask) a[i] ^= a[i ^ mask];
    for (int mask = 1; mask < n; mask <<= 1)
        for (int i = 0; i < n; ++i)
            if ((i & mask) && (i ^ mask) < n) a[i ^ mask] ^= a[i];
    for (int i = n - 1; i >= 0; --i) printf("%d%c", a[i], " \n"[i == 0]);
}
