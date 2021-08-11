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
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        if (x < n / k)
            cout << -1 << '\n';
        else {
            const ll inf = 1e18;
            vector dp(n + 1, vector(x + 1, -inf));
            vector<deque<pair<ll, int>>> max_deque(x + 1);
            dp[0][x] = 0;
            for (int i = 1; i <= n; ++i) {
                for (int remaining = x; remaining >= 0; --remaining) {
                    ll cur = dp[i - 1][remaining];
                    auto& cur_deque = max_deque[remaining];
                    while (!cur_deque.empty() && cur >= cur_deque.back().first)
                        cur_deque.pop_back();
                    cur_deque.emplace_back(cur, i - 1);
                    if (cur_deque.front().second == i - k - 1)
                        cur_deque.pop_front();
                }
                for (int remaining = x - 1; remaining >= 0; --remaining)
                    dp[i][remaining] =
                        max(dp[i][remaining],
                            max_deque[remaining + 1].front().first + a[i - 1]);
            }
            ll ans = -inf;
            for (int i = n - k + 1; i <= n; ++i) ans = max(ans, dp[i][0]);
            assert(ans != -inf);
            cout << ans << '\n';
        }
    }
}


