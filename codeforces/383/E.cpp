#include <bits/stdc++.h>
using namespace std;

const int m = 24;
const int M = 1 << m;
int dp[M] = {0};

int main () {
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, e, ans = 0, i, j, mask;
    string s;
    cin >> n;
    
    for (i = 0; i < n; ++i) {
        cin >> s;
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
    
    cout << ans << "\n";
}
