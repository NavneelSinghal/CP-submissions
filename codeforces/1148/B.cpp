#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

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
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, m, ta, tb, k;
        cin >> n >> m >> ta >> tb >> k;
        if (k >= min(n, m)) {
            cout << -1 << '\n';
        } else {
            vector<int> a(n), b(m);
            for (auto& x : a) cin >> x, x += ta;
            for (auto& x : b) cin >> x;
            bool disconnect = false;
            int ans = 0;
            for (int r = 0; r <= k; ++r) {
                // remove r from a
                int first_in_a = r;
                int first_in_b = lower_bound(begin(b), end(b), a[first_in_a]) - begin(b) + k - r;
                if (first_in_b >= m) {
                    disconnect = true;
                    break;
                } else {
                    ans = max(ans, b[first_in_b] + tb);
                }
            }
            if (disconnect) {
                cout << -1 << '\n';
            } else {
                cout << ans << '\n';
            }
        }
    }
}
