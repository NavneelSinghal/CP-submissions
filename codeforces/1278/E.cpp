#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
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
        vector<pair<int, int>> events{pair{0, 0}};
        auto dfs = [&g, &events](const auto& self, int u, int p) -> void {
            vector<int> order;
            for (auto v : g[u]) if (v != p) order.push_back(v);
            while (!order.empty()) {
                events.emplace_back(order.back(), 0);
                order.pop_back();
            }
            events.emplace_back(u, 1);
            for (auto v : g[u]) if (v != p) self(self, v, u);
        };
        dfs(dfs, 0, -1);
        vector<int> l(n), r(n);
        for (int i = 0; i < 2 * n; ++i) {
            auto [index, type] = events[i];
            if (type == 0) l[index] = i + 1;
            else r[index] = i + 1;
        }
        for (int i = 0; i < n; ++i) {
            cout << l[i] << ' ' << r[i] << '\n';
        }
    }
}
