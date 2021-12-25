#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        ll n, X;
        cin >> n >> X;
        vector<vector<int>> balls(n);
        for (auto& x : balls) {
            int k;
            cin >> k;
            x.resize(k);
            for (auto& y : x) cin >> y;
        }
        int ans = 0;
        auto rec = [&](const auto& self, int i, ll prod) -> void {
            if (i == n) {
                if (prod == 1) ans++;
                return;
            }
            for (auto x : balls[i]) {
                if (prod % x == 0) {
                    self(self, i + 1, prod / x);
                }
            }
        };
        rec(rec, 0, X);
        cout << ans << '\n';
    }
}
