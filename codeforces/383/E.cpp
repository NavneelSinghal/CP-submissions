#include <bits/stdc++.h>
using namespace std;

const int m = 24, M = 1 << m, M2 = M >> 1;
int dp[M] = {0}, n, e, ans = 0, i, j, v, w, mask, cur = 0;
char s[4];

int main () {

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s", s);
        e = 0;
        for (j = 0; j < 3; ++j) e |= (1 << (s[j] - 'a'));
        dp[e]++;
    }

    for (i = 1; i < M; i <<= 1) {
        v = i - 1;
        w = - i;
        for (mask = 0; mask < M2; ++mask) {
            cur = (v & mask) | ((mask & w) << 1);
            dp[cur ^ i] += dp[cur];
        }
    }

    for (i = 0; i < M; ++i) {
        ans ^= (n - dp[i]) * (n - dp[i]);
    }

    printf("%d\n", ans);
}
