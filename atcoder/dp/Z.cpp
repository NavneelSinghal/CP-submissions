#ifndef DEBUG
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#endif

#include <bits/stdc++.h>

using ll = int64_t;

constexpr ll inf = 1e18;
template <typename T, T x_low, T x_high, T id>
struct LiChaoTree {
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
        inline T get(T x) const { return a * x + b; }
    };

    struct Node {
        Line x;
        Node *l, *r;
        Node(const Line& x) : x{x}, l{nullptr}, r{nullptr} {}
    };

    Node* root;

    LiChaoTree() : root{nullptr} {}

    ~LiChaoTree() { cleanup(root); }

    void cleanup(Node* node) {
        if (node) cleanup(node->l), cleanup(node->r), delete node;
    }

    Node* update(Node* t, Line& x, const T& l, const T& r, const T& x_l,
                 const T& x_r) {
        if (!t) return new Node(x);
        auto t_l = t->x.get(l), t_r = t->x.get(r);
        if (t_l <= x_l && t_r <= x_r) {
            return t;
        } else if (t_l >= x_l && t_r >= x_r) {
            t = new Node(*t);
            t->x = x;
            return t;
        } else {
            T m = (l + r) / 2;
            auto t_m = t->x.get(m), x_m = x.get(m);
            t = new Node(*t);
            if (t_m > x_m) {
                std::swap(t->x, x);
                if (x_l >= t_l)
                    t->l = update(t->l, x, l, m, t_l, t_m);
                else
                    t->r = update(t->r, x, m + 1, r, t_m + x.a, t_r);
            } else {
                if (t_l >= x_l)
                    t->l = update(t->l, x, l, m, x_l, x_m);
                else
                    t->r = update(t->r, x, m + 1, r, x_m + x.a, x_r);
            }
            return t;
        }
    }

    void update(const T& a, const T& b) {
        Line x(a, b);
        root = update(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    T query(const Node* t, const T& l, const T& r, const T& x) const {
        if (!t) return id;
        if (l == r) return t->x.get(x);
        T m = (l + r) / 2;
        if (x <= m)
            return std::min(t->x.get(x), query(t->l, l, m, x));
        else
            return std::min(t->x.get(x), query(t->r, m + 1, r, x));
    }

    T query(const T& x) const { return query(root, x_low, x_high, x); }
};

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        ll C;
        cin >> C;
        vector<ll> h(n);
        for (auto& x : h) cin >> x;
        // cost = hj^2 + hi^2 - 2 * hi * hj + C
        vector<ll> dp(n);
        dp[0] = 0;
        LiChaoTree<int64_t, int64_t(0), int64_t(1e6), int64_t(1e18)> lichao;
        lichao.update(-2 * h[0], h[0] * h[0]);
        for (int i = 1; i < n; ++i) {
            dp[i] = C + h[i] * h[i] + lichao.query(h[i]);
            lichao.update(-2 * h[i], h[i] * h[i] + dp[i]);
        }
        cout << dp[n - 1] << '\n';
    }
}