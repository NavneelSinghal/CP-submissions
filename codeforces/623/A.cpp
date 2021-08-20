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
        string ans(n, 'x');
        for (int i = 0; i < n; ++i)
            if ((int)g[i].size() == n - 1) ans[i] = 'b';
        auto G = g;
        for (int i = 0; i < n; ++i) {
            if (ans[i] == 'b')
                G[i].clear();
            else
                G[i].erase(remove_if(begin(G[i]), end(G[i]),
                                     [&](int k) { return ans[k] == 'b'; }),
                           end(G[i]));
        }
        vector<vector<int>> components;
        vector<bool> visited(n, false);
        const auto dfs = [&](const auto& self, int u) -> void {
            components.back().push_back(u);
            visited[u] = true;
            for (auto v : G[u])
                if (!visited[v]) self(self, v);
        };
        string s = "ac";
        bool works = true;
        for (int i = 0; i < n; ++i) {
            if (ans[i] != 'b' && !visited[i]) {
                if (components.size() == 2) {
                    works = false;
                    break;
                }
                char c = s[components.size()];
                components.emplace_back();
                dfs(dfs, i);
                for (auto j : components.back()) ans[j] = c;
            }
        }
        if (!works) {
            cout << "No\n";
            continue;
        }
        decltype(g) check(n);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (abs(ans[i] - ans[j]) <= 1)
                    check[i].push_back(j), check[j].push_back(i);
        for (auto& x : g) sort(begin(x), end(x));
        if (check == g)
            cout << "Yes\n" << ans << '\n';
        else
            cout << "No\n";
    }
}
