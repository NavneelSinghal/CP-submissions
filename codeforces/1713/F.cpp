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

// 1 2 3 4 5 6 7 8 9 10
void print_non_negative(int x) {
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
