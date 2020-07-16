#include <bits/stdc++.h>
using namespace std;

const int m = 20;
const int M = 1 << m;
vector<int> dp(M);

const int mod = 1e9 + 7;

int power (long long a, int n) {
    long long res = 1;
    while (n) {
        if (n & 1) res = (res * a) % mod;
        if (n >>= 1) a = (a * a) % mod;
    }
    return res;
}

int main () {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        dp[x]++;
    }
    for (int i = 1; i < M; i <<= 1) {
        for (int mask = 0; mask < M; ++mask) {
            if (mask & i) {
                dp[i ^ mask] += dp[mask];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < M; i++) {
        ans += ((__builtin_popcount(i) & 1) ? -1 : 1) * power(2, dp[i]);
        if (ans < 0) ans += mod;
        else if (ans >= mod) ans -= mod;
    }

    cout << ans << endl;

}
