#include <bits/stdc++.h>
using namespace std;

const int m = 24;
const int M = 1 << m;
int dp[M] = {0};

int main () {
    
    int n, e, ans = 0, i, j, mask;
    char s[4];
    scanf("%d", &n);
    
    for (i = 0; i < n; ++i) {
        scanf("%s", s);
        e = 0;
        for (j = 0; j < 3; ++j) e |= (1 << (s[j] - 'a'));
        dp[e]++;
    }

    for (i = 1; i < M; i <<= 1) {
        for (mask = 0; mask < M; ++mask) {
            if (i & mask) {
                dp[mask] += dp[mask ^ i];
            }
        }
    }

    for (i = 0; i < M; ++i) {
        ans ^= (n - dp[i]) * (n - dp[i]);
    }
    
    printf("%d\n", ans);
}
