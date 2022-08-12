#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define ll long long
#define N 200000
#define LG 20

ll read() {
    ll f = 0;
    ll fu = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') fu = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        f = (f << 3) + (f << 1) + (c & 15);
        c = getchar();
    }
    f *= fu;
    return f;
}

void print(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10)
        putchar(x + 48);
    else
        print(x / 10), putchar(x % 10 + 48);
}

ll abs(ll a) {
    return a < 0 ? -a : a;
}

ll gcd(ll a, ll b) {
    if (!a || !b) return a | b;
    int c = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    b >>= __builtin_ctzll(b);
    if (a < b) {
        ll t = a;
        a = b;
        b = t;
    }
    while (b) {
        do {
            a -= b;
            a >>= __builtin_ctzll(a);
        } while (a >= b);
        ll t = a;
        a = b;
        b = t;
    }
    return a << c;
}

ll a[LG][N];
int lg[N + 1];

void build(int n) {
    for (int h = 1; (1 << h) <= n; ++h)
        for (int i = 0; i + (1 << h) <= n; ++i)
            a[h][i] = gcd(a[h - 1][i], a[h - 1][i + (1 << (h - 1))]);
}

ll query(int l, int r) {
    if (l > r) return 0;
    if (l == r) return a[0][l];
    int h = lg[r - l + 1];
    return gcd(a[h][l], a[h][r - (1 << h) + 1]);
}

int main() {
    lg[1] = 0;
    for (int i = 2; i < N; ++i) lg[i] = lg[i >> 1] + 1;
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) a[0][i] = read();
        if (n == 1) {
            print(1);
            putchar('\n');
            continue;
        }
        --n;
        for (int i = 0; i < n; ++i) a[0][i] = abs(a[0][i] - a[0][i + 1]);
        build(n);
        int ans = 0;
        int l = -1, r = -1;
        while (++l < n) {
            while (l <= r) {
                ll g = query(l, r);
                if (g != 1) {
                    break;
                } else {
                    ++l;
                }
            }
            if (r - l + 1 > ans) ans = r - l + 1;
            while (r + 1 < n) {
                ll g = query(l, r + 1);
                if (g == 1) {
                    break;
                } else {
                    ++r;
                }
            }
            if (r - l + 1 > ans) ans = r - l + 1;
        }
        print(ans + 1);
        putchar('\n');
    }
}
