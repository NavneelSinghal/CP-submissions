#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

struct DSURollbacks {
   private:
    // negative - size; happens at the root
    // non-negative - parent; happens at non-root
    std::vector<int> parent_or_size;
    std::vector<std::array<int, 4>> history;
    static constexpr int inf = 1e9;

   public:
    DSURollbacks(int n) : parent_or_size(n, -1) {}
    int root(int v) {
        if (parent_or_size[v] < 0) return v;
        return root(parent_or_size[v]);
    }
    bool join(int u, int v) {
        u = root(u);
        v = root(v);
        if (u == v) {
            history.emplace_back(std::array{inf, inf, inf, inf});
            return false;
        } else {
            if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);
            history.emplace_back(std::array{u, v, parent_or_size[u], parent_or_size[v]});
            parent_or_size[u] += parent_or_size[v];
            parent_or_size[v] = u;
            return true;
        }
    }
    void rollback() {
        auto [u, v, psu, psv] = history.back();
        history.pop_back();
        if (u != inf) parent_or_size[u] = psu, parent_or_size[v] = psv;
    }
};

struct edge {
    int u, v;
    int w;
    bool operator<(const edge& e) { return w < e.w; }
};

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, m;
        cin >> n >> m;
        DSURollbacks dsu(n);
        vector<edge> edges(m);
        int maxw = 0;
        for (auto& [u, v, w] : edges)
            cin >> u >> v >> w, --u, --v, maxw = max(w, maxw);
        maxw++;
        vector<vector<edge>> g(maxw);
        for (auto& [u, v, w] : edges) g[w].push_back({u, v, w});
        vector<vector<vector<pair<edge, int>>>> queries(maxw);
        auto sorted_edges = edges;
        sort(begin(sorted_edges), end(sorted_edges));
        int q;
        cin >> q;
        vector<int> works(q, 1);
        for (int i = 0; i < q; ++i) {
            int sz;
            cin >> sz;
            vector<int> edge_ids(sz);
            for (auto& x : edge_ids) cin >> x, --x;
            sort(begin(edge_ids), end(edge_ids),
                 [&](int i, int j) { return edges[i] < edges[j]; });
            for (auto edge_id : edge_ids) {
                auto edge = edges[edge_id];
                if (queries[edge.w].empty() ||
                    queries[edge.w].back().back().second != i)
                    queries[edge.w].emplace_back();
                queries[edge.w].back().emplace_back(edge, i);
            }
        }
        for (int w = 1; w < maxw; ++w) {
            for (auto& x : queries[w]) {
                for (auto& [edge, query_index] : x) {
                    auto [u, v, w] = edge;
                    if (!dsu.join(u, v)) works[query_index] = false;
                }
                for (int i = 0; i < (int)x.size(); ++i) dsu.rollback();
            }
            for (auto& [u, v, w] : g[w]) dsu.join(u, v);
        }
        for (int i = 0; i < q; ++i) {
            cout << (works[i] ? "YES" : "NO") << '\n';
        }
    }
}
