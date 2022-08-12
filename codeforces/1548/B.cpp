#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define ll long long
#define N 200000
#define LG 20

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
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
        for (int i = 0; i < n; ++i) scanf("%lld", &a[0][i]);
        if (n == 1) {
            printf("1\n");
            continue;
        }
        --n;
        for (int i = 0; i < n; ++i) a[0][i] -= a[0][i + 1];
        build(n);
        int ans = 0;
        int l = -1, r = -1;
        while (++l < n) {
            if (r < l - 1) r = l - 1;
            while (l <= r) {
                ll g = query(l, r);
                if (g != 1 && g != -1) {
                    break;
                } else {
                    ++l;
                }
            }
            if (r - l + 1 > ans) ans = r - l + 1;
            ll g = query(l, r);
            while (r + 1 < n) {
                g = gcd(g, a[0][r + 1]);
                if (g == 1 || g == -1) {
                    break;
                } else {
                    ++r;
                }
            }
            if (r - l + 1 > ans) ans = r - l + 1;
        }
        printf("%d\n", ans + 1);
    }
}
