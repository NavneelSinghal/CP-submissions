#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 3e18L;

template <bool is_lazy = true>
struct LazySegTree {
    struct node_t {
        // f[i] = dist from root
        // max1 = max (f[i])
        // max2 = max (- 2 * f[j])
        // max3 = max (f[i] - 2 * f[j])
        // max4 = max (- 2 * f[j] + f[k])
        // max5 = max (f[i] - 2 * f[j] + f[k])
        ll max1, max2, max3, max4, max5;
    };
    using base_t = ll;
    using update_t = ll;

    // combining two nodes
    inline node_t combine(const node_t &n1, const node_t &n2) const {
        if (n1.max1 == -inf) return n2;
        if (n2.max1 == -inf) return n1;
        node_t ret;
        ret.max1 = max(n1.max1, n2.max1);
        ret.max2 = max(n1.max2, n2.max2);
        ret.max3 = max({n1.max3, n2.max3, n1.max1 + n2.max2});
        ret.max4 = max({n1.max4, n2.max4, n1.max2 + n2.max1});
        ret.max5 =
            max({n1.max5, n2.max5, n1.max1 + n2.max4, n1.max3 + n2.max1});
        return ret;
    }

    // create node from base value and index i
    inline node_t make_node(const base_t &val, int i) const {
        return {val, -2 * val, -val, -val, 0LL};
    }

    // node corresponding to empty interval
    inline node_t id_node() const { return {-inf, -2 * inf, -inf, -inf, -inf}; }

    // apply update u to the whole node n
    inline node_t apply_update(const update_t &u, const node_t &nd) const {
        if (nd.max1 == -inf) return nd;
        node_t ret = nd;
        ret.max1 += u;
        ret.max2 -= 2 * u;
        ret.max3 -= u;
        ret.max4 -= u;
        return ret;
    }

    // effective update if v is applied to node, followed by u
    inline update_t compose_updates(const update_t &u,
                                    const update_t &v) const {
        return u + v;
    }

    // identity update
    inline update_t id_update() const { return 0; }

    std::vector<node_t> t;
    std::vector<update_t> lazy;
    int n;

    LazySegTree(int n) {
        this->n = n;
        if (this->n == 0) return;
        this->t.assign(2 * n - 1, id_node());
        if constexpr (is_lazy) this->lazy.assign(2 * n - 1, id_update());
        std::vector<base_t> a(n, 0);
        _build(0, 0, n, a);
    }

    LazySegTree(std::vector<base_t> &a) {
        this->n = (int)a.size();
        if (this->n == 0) return;
        this->t.assign(2 * a.size() - 1, id_node());
        if constexpr (is_lazy) this->lazy.assign(2 * a.size() - 1, id_update());
        _build(0, 0, n, a);
    }

    // half open
    void update(int l, int r, const update_t &u) {
        if constexpr (!is_lazy) assert(l == r - 1);
        ql = l, qr = r;
        if (l >= r) return;
        _update(0, 0, n, u);
    }
    node_t query(int l, int r) {
        ql = l, qr = r;
        if (l >= r) return id_node();
        return _query(0, 0, n);
    }

    template <bool b = is_lazy, typename F>
    int first_false_right(int l, const F &f) {
        auto acc = id_node();
        ql = l, qr = n;
        auto i = _first_false_right<b, F>(0, 0, n, f, acc);
        if (i == -1) return n;
        return i;
    }

   private:
    int ql, qr;
    // helper functions
    inline void _pullUp(int v, int l, int m) {
        t[v] = combine(t[v + 1], t[v + ((m - l) << 1)]);
    }
    inline void _updateNode(int v, const update_t &u) {
        t[v] = apply_update(u, t[v]);
        if constexpr (is_lazy) lazy[v] = compose_updates(u, lazy[v]);
    }
    inline void _pushDown(int v, int l, int m) {
        if constexpr (!is_lazy) return;
        if (lazy[v] == id_update()) return;
        _updateNode(v + 1, lazy[v]);
        _updateNode(v + ((m - l) << 1), lazy[v]);
        lazy[v] = id_update();
    }

    // actual functions
    void _build(int v, int l, int r, const std::vector<base_t> &a) {
        if (l == r - 1) {
            t[v] = make_node(a[l], l);
            return;
        }
        int m = (l + r) / 2;
        _build(v + 1, l, m, a);
        _build(v + ((m - l) << 1), m, r, a);
        _pullUp(v, l, m);
    }

    // only go down branches with at non-empty intersection, same for _query
    void _update(int v, int l, int r, const update_t &u) {
        if (ql <= l && r <= qr) {  // completely inside query
            _updateNode(v, u);
            return;
        }
        int m = (l + r) / 2;
        _pushDown(v, l, m);
        if (ql < m) _update(v + 1, l, m, u);
        if (m < qr) _update(v + ((m - l) << 1), m, r, u);
        _pullUp(v, l, m);
    }

    node_t _query(int v, int l, int r) {
        if (ql <= l && r <= qr) return t[v];  // completely inside query
        int m = (l + r) / 2;
        _pushDown(v, l, m);
        if (m >= qr) return _query(v + 1, l, m);
        if (m <= ql) return _query(v + ((m - l) << 1), m, r);
        return combine(_query(v + 1, l, m), _query(v + ((m - l) << 1), m, r));
    }

    template <bool b = true, typename F>
    int _first_false_right(int v, int l, int r, const F &f, node_t &acc) {
        if (r <= ql) return -1;
        if (qr <= l) return l;
        auto new_acc = combine(acc, t[v]);
        if (ql <= l && r <= qr && f(new_acc)) {
            acc = new_acc;
            return -1;
        }
        if (l == r - 1) return l;
        int m = (r + l) / 2;
        if constexpr (b) _pushDown(v, l, m);
        if (ql < m) {
            auto res = _first_false_right<b, F>(v + 1, l, m, f, acc);
            if (res != -1) return res;
        }
        if (m < qr)
            return _first_false_right<b, F>(v + ((m - l) << 1), m, r, f, acc);
        return -1;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;

    while (t--) {
        int n, q;
        ll w;
        cin >> n >> q >> w;

        vector<vector<int>> g(n);
        vector<tuple<int, int, ll>> edges(n - 1);

        for (int i = 1; i < n; ++i) {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            --u, --v;
            g[u].push_back(i - 1);
            g[v].push_back(i - 1);
            edges[i - 1] = {u, v, c};
        }

        auto other = [&](int i, int u) -> int {
            auto &[uu, vv, ww] = edges[i];
            if (uu == u)
                return vv;
            else
                return uu;
        };

        vector<int> in_time(n, -1), out_time(n, -1), par(n, -1);
        auto dfs_time_dist = [&](const auto &self, int u = 0, int p = 0,
                                 int timer = 0) -> int {
            in_time[u] = timer++;
            par[u] = p;
            for (auto i : g[u]) {
                int v = other(i, u);
                if (v == p) continue;
                timer = self(self, v, u, timer) + 1;
            }
            return out_time[u] = timer;
        };
        int final_timer = dfs_time_dist(dfs_time_dist);
        LazySegTree<true> seg(2 * n - 1);
        for (int i = 1; i < n; ++i) {
            auto [u, v, weight] = edges[i - 1];
            if (v == par[u]) swap(u, v);
            seg.update(in_time[v], out_time[v], weight);
        }
        ll last = 0;
        while (q--) {
            int d;
            ll e;
            cin >> d >> e;
            int edge_index = (d + last) % (n - 1);
            ll new_edge_weight = (e + last) % w;
            auto [u, v, old_edge_weight] = edges[edge_index];
            edges[edge_index] = {u, v, new_edge_weight};
            if (v == par[u]) swap(u, v);
            seg.update(in_time[v], out_time[v],
                       new_edge_weight - old_edge_weight);
            last = seg.query(0, 2 * n - 1).max5;
            cout << last << '\n';
        }
    }
}
