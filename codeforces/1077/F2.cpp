#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, k, x;
        cin >> n >> k >> x;
        vector<ll> a(n);
        for (auto& y : a) cin >> y;
        if (x < n / k)
            cout << -1 << '\n';
        else {
            vector dp(n + 1, vector(x + 1, ll(-1)));
            dp[0][x] = 0;
            for (int remaining = x - 1; remaining >= 0; --remaining) {
                deque<int> q;
                q.push_back(0);
                for (int i = 1; i <= n; ++i) {
                    while (!q.empty() && q.front() < i - k) q.pop_front();
                    if (!q.empty() && dp[q.front()][remaining + 1] != -1)
                        dp[i][remaining] =
                            dp[q.front()][remaining + 1] + a[i - 1];
                    while (!q.empty() &&
                           dp[q.back()][remaining + 1] < dp[i][remaining + 1])
                        q.pop_back();
                    q.push_back(i);
                }
            }
            ll ans = -1;
            for (int i = n - k + 1; i <= n; ++i)
                ans = max(ans, dp[i][0]);
            cout << ans << '\n';
        }
    }
}

