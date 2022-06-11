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
using ull = uint64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int ans = int(1e9);
        auto dfs = [&](auto self, int u, int p, int rem) -> void {
            if (p == -1) {
                if (g[u].size() == 0) {
                    ans = min(ans, rem);
                } else if (g[u].size() == 1) {
                    ans = min(ans, rem + 1);
                } else {
                    for (auto v : g[u]) if (v != p) self(self, v, u, rem + 2);
                }
            } else {
                if (g[u].size() == 1) {
                    ans = min(ans, rem);
                } else if (g[u].size() == 2) {
                    ans = min(ans, rem + 1);
                } else {
                    for (auto v : g[u]) if (v != p) self(self, v, u, rem + 2);
                }
            }
        };
        dfs(dfs, 0, -1, 1);
        cout << n - ans << '\n';
    }
}

