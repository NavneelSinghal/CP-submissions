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
        int n, m;
        cin >> n >> m;
        struct edge {
            int v, w;
        };
        vector<basic_string<edge>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].push_back(edge{v, w});
            g[v].push_back(edge{u, w});
        }
        int ans = (1 << 30) - 1;
        for (int bit = 29; bit >= 0; --bit) {
            ans ^= 1 << bit;
            vector<int> visited(n);
            int cnt = 0;
            auto dfs = [&](const auto& self, int u) -> void {
                ++cnt;
                visited[u] = 1;
                for (auto [v, w] : g[u])
                    if (!visited[v] && !(w & ~ans)) self(self, v);
            };
            dfs(dfs, 0);
            if (cnt != n) ans ^= 1 << bit;
        }
        cout << ans << '\n';
    }
}

