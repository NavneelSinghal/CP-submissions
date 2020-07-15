#include <bits/stdc++.h>
using namespace std;

const int m = 24;
const int M = 1 << m;
int dp[M] = {0};

int main () {
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        unsigned e = 0;
        for (int j = 0; j < 3; ++j) {
            int pos = s[j] - 'a';
            e |= (1 << pos);
        }
        dp[e]++;
    }

    for (int i = 1; i < M; i <<= 1) {
        for (int mask = 0; mask < M; ++mask) {
            if (i & mask) {
                dp[mask] += dp[mask ^ i];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < M; ++i) {
        ans ^= (n - dp[i]) * (n - dp[i]);
    }
    
    cout << ans << "\n";
}
