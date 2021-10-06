#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

template <class T, class Combine, class Subtract>
struct Fenwick {
    Fenwick(int _n, const T& _id_node, const Combine& _combine,
            const Subtract& _subtract)
        : n(_n),
          t(_n + 1, _id_node),
          id_node(_id_node),
          combine(_combine),
          subtract(_subtract) {}

    Fenwick(const std::vector<T>& v, const T& _id_node, const Combine& _combine,
            const Subtract& _subtract)
        : n((int)v.size()),
          t(n + 1),
          id_node(_id_node),
          combine(_combine),
          subtract(_subtract) {
        std::copy(std::begin(v), std::end(v), std::begin(t) + 1);
        build();
    }

    void build() {
        for (int i = 1, j = 2; i <= n; ++i, j = (i & -i) + i)
            if (j <= n) t[j] = combine(t[j], t[i]);
    }

    // prefix_sum[0..i)
    T query(int i) {
        T s = id_node;
        for (; i; i -= (i & -i)) s = combine(s, t[i]);
        return s;
    }

    // range query [l, r)
    // more efficient if subtraction is relatively slow
    T query_single_subtraction(int l, int r) {
        T s_l = id_node, s_r = id_node;
        for (; r; r -= (r & -r)) s_r = combine(s_r, t[r]);
        for (; l; l -= (l & -l)) s_l = combine(s_l, t[l]);
        return subtract(s_r, s_l);
    }

    // range query [l, r)
    T query(int l, int r) {
        T s = id_node;
        for (; r; r -= (r & -r)) s = combine(s, t[r]);
        for (; l; l -= (l & -l)) s = subtract(s, t[l]);
        return s;
    }

    // increase a[i] by v
    void update(int i, const T& v) {
        for (++i; i <= n; i += i & (-i)) t[i] = combine(t[i], v);
    }

    // call build after all the calls to set/add
    void set(int i, const T& v) { t[i + 1] = v; }
    void add(int i, const T& v) { t[i + 1] = combine(t[i + 1], v); }

   private:
    int n;
    std::vector<T> t;
    const T id_node;
    Combine combine;
    Subtract subtract;
};

template <class T>
auto compress(const vector<T>& a) {
    int n = int(size(a));
    vector<pair<T, int>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first) ++rnk;
        compressed[p[k].second] = rnk;
    }
    return compressed;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(6) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        a = compress(a);
        using Node = int64_t;
        const Node id_node = 0;
        auto combine = [](const Node& a, const Node& b) {
            return a + b;
        };
        auto subtract = [](const Node& a, const Node& b) {
            return a - b;
        };
        Fenwick left(n, id_node, combine, subtract);
        Fenwick right(n, id_node, combine, subtract);
        for (int i = 0; i < n; ++i) right.add(a[i], 1);
        right.build();
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += 1LL * (i - left.query(a[i] + 1)) * right.query(a[i]);
            left.update(a[i], 1);
            right.update(a[i], -1);
        }
        cout << ans << '\n';
    }
}
