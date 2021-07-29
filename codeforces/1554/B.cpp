#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        ll ans = -1e18;
        for (int i = max(0, n - 2 * k - 1); i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ans = max(ans, ll(i + 1) * (j + 1) - k * (a[i] | a[j]));
            }
        }
        cout << ans << '\n';
    }
}

