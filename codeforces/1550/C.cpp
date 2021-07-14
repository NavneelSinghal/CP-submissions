#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;

using namespace std;

template <class T>
auto compress(const vector<T>& a) {
    int n = size(a);
    vector<pair<T, int>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    vector<T> vals;
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals.push_back(p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return make_pair(compressed, vals);
}

// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
struct lazy_segtree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;

   public:
    template <typename... T>
    explicit lazy_segtree(int n, const Base& id_base, T... args)
        : lazy_segtree(std::vector<Base>(n, id_base), args...) {}
    explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr)
        : _n(int(v.size())),
          make_node(_make_node),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        build(v);
    }

    void build(const std::vector<Base>& v) {
        _n = int(v.size());
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<Node>(2 * size, id_node);
        if constexpr (is_lazy) lz = std::vector<Update>(size, id_update);
        for (int i = 0; i < _n; i++) d[size + i] = make_node(v[i], i);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    
    void set(int p, Node x) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; ++i) update(p >> i);
    }

    Node get(int p) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    Node query(int l, int r) {
        if (l == r) return id_node;
        l += size, r += size;
        int l_ctz = __builtin_ctz(l);
        int r_ctz = __builtin_ctz(r);
        if constexpr (is_lazy) {
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        Node sml = id_node, smr = id_node;
        while (l < r) {
            if (l & 1) sml = combine(sml, d[l++]);
            if (r & 1) smr = combine(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return combine(sml, smr);
    }
    Node all_query() { return d[1]; }
    void update(int p, Update f) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply_update(f, d[p]);
        for (int i = 1; i <= log; ++i) update(p >> i);
    }
    void update(int l, int r, Update f) {
        if (l == r) return;
        l += size, r += size;
        int l_ctz = __builtin_ctz(l);
        int r_ctz = __builtin_ctz(r);
        if constexpr (is_lazy) {
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
        for (int i = l_ctz + 1; i <= log; ++i) update(l >> i);
        for (int i = r_ctz + 1; i <= log; ++i) update((r - 1) >> i);
    }

    template <bool (*g)(Node)>
    int max_right(int l) {
        return max_right(l, [](Node x) { return g(x); });
    }
    template <class G>
    int max_right(int l, G g) {
        // assert(0 <= l && l <= _n);
        // assert(g(id_node));
        if (l == _n) return _n;
        l += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(l >> i);
        Node sm = id_node;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(combine(sm, d[l]))) {
                while (l < size) {
                    if constexpr (is_lazy) push(l);
                    l = (2 * l);
                    if (g(combine(sm, d[l]))) {
                        sm = combine(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = combine(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(Node)>
    int min_left(int r) {
        return min_left(r, [](Node x) { return g(x); });
    }
    template <class G>
    int min_left(int r, G g) {
        // assert(0 <= r && r <= _n);
        // assert(g(id_node));
        if (r == 0) return 0;
        r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push((r - 1) >> i);
        Node sm = id_node;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(combine(d[r], sm))) {
                while (r < size) {
                    if constexpr (is_lazy) push(r);
                    r = (2 * r + 1);
                    if (g(combine(d[r], sm))) {
                        sm = combine(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = combine(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

   private:
    int _n, size, log;
    std::vector<Node> d;
    std::vector<Update> lz;
    const MakeNode make_node;
    const CombineNodes combine;
    const Node id_node;
    const ApplyUpdate apply_update;
    const Update id_update;
    const ComposeUpdates compose_updates;

    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id_update;
    }
};
// clang-format on

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<int> nxt_ge(n, n);
        vector<int> nxt_le(n, n);
        stack<int> s;
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] < a[i]) s.pop();
            if (!s.empty()) nxt_ge[i] = s.top();
            s.push(i);
        }
        stack<int>().swap(s);
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] > a[i]) s.pop();
            if (!s.empty()) nxt_le[i] = s.top();
            s.push(i);
        }
        vector<int> closest_ge(n, n);
        vector<int> closest_le(n, n);
        const auto rec = [&](const auto& self, int l, int r) -> void {
            if (l >= r) return;
            int m = (l + r + 1) / 2;
            vector<int> temp(a.begin() + l, a.begin() + r + 1);
            auto [compressed, vals] = compress(temp);
            int sz = temp.size();
            vector<int> min_nxt_le(sz, n);
            vector<int> min_nxt_ge(sz, n);
            for (int i = m; i <= r; ++i) {
                int loc =
                    lower_bound(begin(vals), end(vals), a[i]) - begin(vals);
                min_nxt_le[loc] = min(min_nxt_le[loc], nxt_le[i]);
                min_nxt_ge[loc] = min(min_nxt_ge[loc], nxt_ge[i]);
            }
            for (int i = 1; i < sz; ++i)
                min_nxt_le[i] = min(min_nxt_le[i], min_nxt_le[i - 1]);
            for (int i = sz - 2; i >= 0; --i)
                min_nxt_ge[i] = min(min_nxt_ge[i], min_nxt_ge[i + 1]);
            for (int i = l; i < m; ++i) {
                int loc =
                    lower_bound(begin(vals), end(vals), a[i]) - begin(vals);
                closest_le[i] = min(closest_le[i], min_nxt_le[loc]);
                closest_ge[i] = min(closest_ge[i], min_nxt_ge[loc]);
            }
            if (l < m - 1) self(self, l, m - 1);
            if (m < r) self(self, m, r);
        };
        rec(rec, 0, n - 1);
        ll ans = 0;

        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; ++i) v[i] = {closest_le[i], closest_ge[i]};
        using Base = pair<int, int>;
        struct Node {
            int le, ge;
        };
        const Node id_node = Node{n, n};
        auto make_node = [](const Base& b, int i) {
            return Node{b.first, b.second};
        };
        auto combine = [](const Node& n, const Node& m) {
            return Node{min(n.le, m.le), min(n.ge, m.ge)};
        };
        using Update = int;
        const Update id_update = 0;
        auto apply_update = [](const Update& u, const Node& n) {
            return n;
        };
        lazy_segtree st(v, id_node, make_node, combine, id_update,
                        apply_update);
        int r = 0;
        for (int i = 0; i < n; ++i) {
            while (r < n) {
                auto nd = st.query(i, r);
                if (!(nd.le > r && nd.ge > r)) break;
                ++r;
            }
            ans += r - i;
        }
        cout << ans << '\n';
    }
}
