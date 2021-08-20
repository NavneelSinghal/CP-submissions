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
    int _tests = 1;
    // cin >> _tests;
    auto yes = [] {
        cout << "Yes\n";
    };
    auto no = [] {
        cout << "No\n";
    };
    for (int _test = 1; _test <= _tests; ++_test) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        debug(g);

        string ans(n, 'x');
        for (int i = 0; i < n; ++i)
            if ((int)g[i].size() == n - 1) ans[i] = 'b';
        debug(ans);
        
        vector<vector<int>> G(n);
        
        for (int i = 0; i < n; ++i)
            if (ans[i] != 'b')
                for (auto x : g[i])
                    if (ans[x] != 'b') G[i].push_back(x);
        debug(G);

        vector<vector<int>> components;
        vector<bool> visited(n, false);
        const auto dfs = [&](const auto& self, int u) -> void {
            components.back().push_back(u);
            visited[u] = true;
            for (auto v : G[u])
                if (!visited[v]) self(self, v);
        };
        bool works = true;
        for (int i = 0; i < n; ++i) {
            if (ans[i] != 'b' && !visited[i]) {
                components.emplace_back();
                dfs(dfs, i);
                for (auto j : components.back()) ans[j] = 'b';
            }
        }
        debug(components);
        if (components.size() > 2) {
            no();
            continue;
        }
        debug("here");
        for (int i = 0; i < (int)components.size(); ++i) {
            char c = (i == 0 ? 'a' : 'c');
            for (auto x : components[i]) {
                ans[x] = c;
            }
        }
        decltype(g) check(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (ans[i] == ans[j] || abs(ans[i] - ans[j]) == 1) {
                    check[i].push_back(j);
                    check[j].push_back(i);
                }
            }
        }
        for (auto& x : g) sort(begin(x), end(x));
        if (check == g) {
            yes();
            cout << ans << '\n';
        } else {
            no();
        }
    }
}

