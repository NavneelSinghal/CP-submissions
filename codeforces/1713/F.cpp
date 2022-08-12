#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdio.h>

#define N 500000

char ibuf[N * 12], obuf[N * 12];
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

void print_non_negative(int x) {
    if (x < 10)
        print_char(x + 48);
    else
        print_non_negative(x / 10), print_char(x % 10 + 48);
}

void print(int x) {
    if (x < 0)
        print_non_negative(-x);
    else
        print_non_negative(x);
}

int main() {
    fread(ibuf + 1, 1, sizeof(ibuf) - 1, stdin);
    int n = read_non_negative();
    static int a[N];
    for (int i = 0; i < n; ++i) a[i] = read_non_negative();
    for (int mask = 1; mask < n; mask <<= 1)
        for (int i = 0; i < n; ++i)
            if (i & mask) a[i] ^= a[i ^ mask];
    for (int mask = 1; mask < n; mask <<= 1)
        for (int i = 0; i < n; ++i)
            if ((i & mask) && (i ^ mask) < n) a[i ^ mask] ^= a[i];
    for (int i = n - 1; i >= 0; --i) {
        print_non_negative(a[i]);
        print_char(" \n"[i == 0]);
    }
    fwrite(obuf, 1, obufptr - obuf, stdout);
}
