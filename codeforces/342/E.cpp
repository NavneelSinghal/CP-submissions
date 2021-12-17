#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();

using ll = long long;
using ld = long double;

using namespace std;

struct HLD_LCA {
    using graph = std::vector<std::vector<int>>;
    HLD_LCA(const graph& G, int root = 0)
        : N((int)G.size()),
          g(G),
          par(N),
          start(N),
          depth(N),
          sz(N),
          in_time(N) {
        par[root] = -1;
        timer = 0;
        dfs_sz(root);
        start[root] = root;
        dfs_hld(root);
    }

    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] > in_time[v];
    }

    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto& v : g[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(begin(g[v]), end(g[v]), u));
            dfs_sz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        in_time[u] = timer++;
        for (auto& v : g[u]) {
            start[v] = (v == g[u][0] ? start[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        for (; start[u] != start[v]; v = par[start[v]])
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    int timer;
};

int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v), g[v].push_back(u);
        }

        // visited[i] = true if we have chosen i as the centroid of some
        // component, equivalent to the fact that these vertices are not in
        // remaining components and also block off the components from each
        // other
        vector<int> visited(n);
        // par[i] = parent of i in the centroid tree
        vector<int> par(n);

        vector<int> sz(n);
        // blocked vertex => size = 0
        auto dfs_sz = [&](const auto& self, int u, int p) -> int {
            if (visited[u]) return 0;
            sz[u] = 1;
            for (auto v : g[u])
                if (v != p) sz[u] += self(self, v, u);
            return sz[u];
        };

        auto dfs_centroid = [&](const auto& self, int u, int p,
                                int limit) -> int {
            for (auto v : g[u])
                if (v != p && !visited[v] && sz[v] > limit)
                    return self(self, v, u, limit);
            return u;
        };

        // p -> parent in the centroid tree
        auto dfs_create = [&](const auto& self, int u, int p) -> void {
            dfs_sz(dfs_sz, u, -1);
            int centroid = dfs_centroid(dfs_centroid, u, -1, sz[u] / 2);
            visited[centroid] = 1;
            par[centroid] = p;
            for (auto v : g[centroid])
                if (!visited[v]) self(self, v, centroid);
        };

        dfs_create(dfs_create, 0, -1);

        HLD_LCA lca(g);
        vector<int> best(n, 1e9);

        auto update = [&](int v) {
            best[v] = 0;
            int u = v;
            while (par[u] != -1) {
                u = par[u];
                best[u] = min(best[u], lca.dist(u, v));
            }
        };

        auto query = [&](int v) {
            int ans = best[v];
            int u = v;
            while (par[u] != -1) {
                u = par[u];
                ans = min(ans, best[u] + lca.dist(u, v));
            }
            return ans;
        };

        update(0);

        for (int i = 0; i < q; ++i) {
            int t, v;
            cin >> t >> v;
            --v;
            if (t == 1) {
                update(v);
            } else {
                cout << query(v) << '\n';
            }
        }
    }
}
