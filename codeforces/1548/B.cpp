#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define ll long long
#define N 200000
#define S 100

ll read() {
    ll f = 0;
    ll fu = 1;
    char c = (char)getchar();
    while (c < '0' || c > '9') {
        if (c == '-') fu = -1;
        c = (char)getchar();
    }
    while (c >= '0' && c <= '9') {
        f = (f << 3) + (f << 1) + (c & 15);
        c = (char)getchar();
    }
    f *= fu;
    return f;
}

void print(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10)
        putchar((char)(x + 48));
    else
        print(x / 10), putchar(x % 10 + 48);
}

ll abs(ll a) {
    return a < 0 ? -a : a;
}

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

ll a[N], distinct[S];
int index[S];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) a[i] = read();
        if (n == 1) {
            print(1);
            putchar('\n');
            continue;
        }
        --n;
        for (int i = 0; i < n; ++i) a[i] = abs(a[i] - a[i + 1]);
        int ans = 0, ptr = 0;
        for (int i = 0; i < n; ++i) {
            distinct[ptr] = a[i];
            index[ptr] = i;
            for (int j = ptr - 1; j >= 0; --j)
                distinct[j] = gcd(distinct[j], distinct[j + 1]);
            int newptr = 0;
            for (int j = 0; j <= ptr; ++j) {
                if (j == 0 || distinct[j] != distinct[j - 1]) {
                    distinct[newptr] = distinct[j];
                    index[newptr] = index[j];
                    ++newptr;
                }
            }
            ptr = newptr;
            if (distinct[0] != 1) {
                if (ans < i + 1) ans = i + 1;
            } else if (newptr > 1) {
                if (ans < i + 1 - index[1]) ans = i + 1 - index[1];
            }
        }
        print(ans + 1);
        putchar('\n');
    }
}
