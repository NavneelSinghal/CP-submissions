#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2")
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
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);  // edge ids
        vector<array<int, 3>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].push_back(i);
            if (u != v) g[v].push_back(i);
            edges[i] = {u, v, w};
        }
        vector<int> marked(m), visited(n), len(n);
        auto dfs = [&](auto self, int u, int path_xor) -> void {
            len[u] = path_xor;
            visited[u] = true;
            for (auto edge : g[u]) {
                auto [U, V, W] = edges[edge];
                auto v = (U == u ? V : U);
                if (v == u) continue;
                if (!visited[v]) {
                    marked[edge] = true;
                    self(self, v, path_xor ^ W);
                }
            }
        };
        dfs(dfs, 0, 0);
        // xor basis
        vector<int> basis;
        auto add = [&basis](int x) {
            for (auto v : basis) x = min(x, x ^ v);
            if (x) basis.push_back(x);
        };
        for (int i = 0; i < m; ++i) {
            if (!marked[i]) {
                auto [U, V, W] = edges[i];
                add(len[U] ^ len[V] ^ W);
            }
        }
        int l = len[n - 1];
        for (auto v : basis) l = min(l, l ^ v);
        cout << l << '\n';
    }
}

