#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>,
           std::vector<int>>
find_scc(const std::vector<std::vector<int>>& g, int const Base = 0) {
    std::vector<int> val, z, component;
    std::vector<std::vector<int>> scc;
    int timer = 0, total_components = 0;
    const auto dfs = [&](const auto& self, int u) -> int {
        int low = val[u] = ++timer;
        int x;
        z.push_back(u);
        for (auto v : g[u])
            if (component[v] < 0)
                low = std::min(low, val[v] ? val[v] : self(self, v));
        if (low == val[u]) {
            scc.emplace_back();
            do {
                x = z.back();
                z.pop_back();
                component[x] = total_components;
                scc.back().push_back(x);
            } while (x != u);
            total_components++;
        }
        return val[u] = low;
    };
    int n = g.size();
    val.assign(n, 0);
    component.assign(n, -1);
    timer = total_components = 0;
    for (int i = 0; i < n; ++i)
        if (component[i] < 0) dfs(dfs, i);
    std::reverse(std::begin(scc), std::end(scc));
    for (int i = 0; i < n; ++i)
        component[i] = total_components - 1 - component[i];
    std::vector<char> seen(n);
    std::vector<std::vector<int>> condensed_graph(total_components);
    for (int i = 0; i < total_components; ++i) {
        for (auto u : scc[i])
            for (auto v : g[u])
                if (component[v] != i && !seen[component[v]])
                    condensed_graph[i].push_back(component[v]),
                        seen[component[v]] = true;
        for (auto v : condensed_graph[i]) seen[v] = false;
    }
    return {scc, condensed_graph, component};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> loop(n);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            if (u == v)
                loop[v] = 1;
            else
                g[u].push_back(v);
        }
        auto [scc, G, comp] = find_scc(g);
        int comps = scc.size();
        vector<int> comp_loop(comps);
        for (int i = 0; i < comps; ++i) {
            if (scc[i].size() > 1)
                comp_loop[i] = 1;
            else if (loop[scc[i][0]])
                comp_loop[i] = 1;
        }
        vector<int> paths(comps);
        paths[comp[0]] = (comp_loop[comp[0]] == 0 ? 1 : -1);
        for (int i = comp[0]; i < comps; ++i) {
            if (paths[i] == 0) {
                continue;
            } else if (paths[i] == 1) {
                for (auto v : G[i]) {
                    if (comp_loop[v]) {
                        paths[v] = -1;
                        continue;
                    }
                    if (paths[v] == -1 || paths[v] == 2) continue;
                    paths[v]++;
                }
            } else if (paths[i] == 2) {
                for (auto v : G[i]) {
                    if (comp_loop[v]) {
                        paths[v] = -1;
                        continue;
                    }
                    if (paths[v] == -1) continue;
                    paths[v] = 2;
                }
            } else if (paths[i] == -1) {
                for (auto v : G[i])
                    paths[v] = -1;
            }
        }
        for (int i = 0; i < n; ++i) cout << paths[comp[i]] << ' ';
        cout << '\n';
    }
    return 0;
}
