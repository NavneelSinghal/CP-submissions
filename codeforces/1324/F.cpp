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

// Fold : Aggregate * Arg * Vertex(int) * EdgeIndex(int) -> Aggregate
template <class Aggregate, class Arg, class Fold>
auto exclusive(const std::vector<Arg>& a, const Aggregate& base, Fold fold,
               int vertex) {
    int n = (int)std::size(a);
    std::vector<Aggregate> b(n, base);
    for (int bit = (int)std::__lg(n); bit >= 0; --bit) {
        for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
        int sz = n - (n & !bit);
        for (int i = 0; i < sz; ++i) {
            int index = (i >> bit) ^ 1;
            b[index] = fold(b[index], a[i], vertex, i);
        }
    }
    return b;
}

// Fold : Aggregate * Arg * Vertex(int) * EdgeIndex(int) -> Aggregate
template <class Arg, class Aggregate, class Fold, class CombineWithRoot>
auto rerooter(const std::vector<std::basic_string<int>>& g, const Arg& arg_base,
              const std::vector<Aggregate>& base, Fold fold,
              CombineWithRoot combine_with_root) {
    int n = (int)std::size(g);

    std::vector<Arg> root_dp(n, arg_base);
    std::vector<std::vector<Arg>> edge_dp(n);

    std::vector<Arg> dp(n, arg_base);

    const auto dfs_compute = [&](auto self, int u, int p) -> void {
        Aggregate aggregate = base[u];
        int edge_index = -1;
        for (auto v : g[u]) {
            edge_index++;
            if (v == p) continue;
            self(self, v, u);
            aggregate = fold(aggregate, dp[v], u, edge_index);
        }
        dp[u] = combine_with_root(aggregate, u);
    };

    dfs_compute(dfs_compute, 0, -1);

    const auto dfs_reroot = [&](auto self, int u, int p) -> void {
        dp[p] = dp[u];
        edge_dp[u].reserve(g[u].size());
        for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
        auto dp_exclusive = exclusive(edge_dp[u], base[u], fold, u);
        assert(dp_exclusive.size() == g[u].size());
        for (int i = 0; i < (int)dp_exclusive.size(); ++i) {
            auto v = g[u][i];
            dp[v] = combine_with_root(dp_exclusive[i], u);
        }
        root_dp[u] =
            combine_with_root(fold(dp_exclusive[0], edge_dp[u][0], u, 0), u);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };

    dfs_reroot(dfs_reroot, 0, 0);

    return make_pair(root_dp, edge_dp);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    std::vector<int> color(n);
    for (auto& x : color) cin >> x;
    std::vector<std::basic_string<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    struct Arg {
        int x;
    };
    struct Aggregate {
        int x;
    };
    auto fold = [](Aggregate vertex_dp, Arg neighbor_dp, int vertex,
                   int edge_index) -> Aggregate {
        return Aggregate{vertex_dp.x + max(0, neighbor_dp.x)};
    };
    auto combine_with_root = [&color](Aggregate vertex_dp, int vertex) -> Arg {
        return Arg{vertex_dp.x + 2 * color[vertex] - 1};
    };
    auto [root_dp, edge_dp] =
        rerooter(g, Arg{0}, std::vector<Aggregate>(n, Aggregate{0}), fold,
                 combine_with_root);
    for (auto& x : root_dp) cout << x.x << ' ';
    cout << '\n';
}

