#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using ll = int64_t;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<set<int>> g(n);
        set<int> not_visited;
        for (int i = 0; i < n; ++i) not_visited.insert(i);
        for (int i = 0, u, v; i < m; ++i) {
            cin >> u >> v;
            --u, --v;
            g[u].insert(v);
            g[v].insert(u);
        }
        vector<vector<int>> components;
        const auto dfs = [&](const auto& self, int u) {
            components.back().push_back(u);
            not_visited.erase(u);
            if (not_visited.empty()) return;
            auto it = not_visited.begin();
            while (true) {
                int v = *it;
                if (g[u].find(v) == g[u].end()) self(self, v);
                it = not_visited.upper_bound(v);
                if (it == not_visited.end()) break;
            }
        };
        for (int i = 0; i < n; ++i) {
            if (not_visited.find(i) != not_visited.end()) {
                components.emplace_back();
                dfs(dfs, i);
            }
        }
        cout << components.size() << '\n';
        vector<int> sz;
        for (auto& c : components) sz.push_back(c.size());
        sort(begin(sz), end(sz));
        for (auto x : sz) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}