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
        for (int h = 1; (1 << h) <= n; ++h)
            for (int i = 0; i + (1 << h) <= n; ++i)
                a[h][i] = gcd(a[h - 1][i], a[h - 1][i + (1 << (h - 1))]);
        int ans = 0;
        int index = 0;
        for (int i = 0; i < n; ++i) {
            int l = i - 1, r = n;
            while (l + 1 < r) {
                int m = l + (r - l) / 2;
                ll g;
                if (m == i) {
                    g = a[0][i];
                } else {
                    int h = lg[m - i + 1];
                    g = gcd(a[h][i], a[h][m - (1 << h) + 1]);
                }
                if (g == 1 || g == -1)
                    r = m;
                else
                    l = m;
            }
            int len = l - i + 1;
            if (len > ans) ans = len, index = i;
        }
        printf("%d\n", ans + 1);
    }
}
