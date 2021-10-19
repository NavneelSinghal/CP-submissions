#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << *ranges::partition_point(views::iota(1, n / k + 1), [&](int m) {
            const int inf = 1e9;
            vector leftmost(k, vector(n + 1, inf));
            for (int bit = 0; bit < k; ++bit) {
                int prv = n;
                for (int i = n - 1; i >= 0; --i) {
                    leftmost[bit][i] = leftmost[bit][i + 1];
                    if (s[i] != '?' and s[i] != 'a' + bit) prv = i;
                    if (prv >= i + m) leftmost[bit][i] = i;
                }
            }
            vector<int> dp(1 << k, inf);
            dp[0] = 0;
            for (int mask = 0; mask < (1 << k); ++mask) {
                if (dp[mask] >= n) continue;
                for (int bit = 0; bit < k; ++bit)
                    if (!((mask >> bit) & 1))
                        dp[mask ^ (1 << bit)] = min(
                            dp[mask ^ (1 << bit)], leftmost[bit][dp[mask]] + m);
            }
            return dp[(1 << k) - 1] <= n;
        }) - 1 << '\n';
    }
}

