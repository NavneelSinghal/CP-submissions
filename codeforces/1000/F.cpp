#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

// Turn off specific target pragmas if using this
static char buf[500 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*)&buf[i -= s];
}
void operator delete(void*) {}

template <class T>
struct ptr {
    unsigned ind;
    ptr(T* p = 0) : ind(p ? unsigned((char*)p - buf) : 0) {
        assert(ind < sizeof buf);
    }
    bool operator==(const ptr other) { return ind == other.ind; }
    T& operator*() const { return *(T*)(buf + ind); }
    T* operator->() const { return &**this; }
    T& operator[](int a) const { return (&**this)[a]; }
    explicit operator bool() const { return ind; }
};

static constexpr bool RESERVE_ROOTS = true;

template <class Node, class Update, class CombineNodes, class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
struct PersistentSegTree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;
    CombineNodes combine;
    Node id_node;
    Update id_update;
    ApplyUpdate apply_update;
    ComposeUpdates compose_updates;
    using ll = long long;
    struct STNode_false {
        Node node;
        ptr<STNode_false> l, r;
        STNode_false() {}
        STNode_false(const Node& _node) : node(_node), l(nullptr), r(nullptr) {}
    };
    struct STNode_true {
        Node node;
        Update update;
        ptr<STNode_true> l, r;
        STNode_true() {}
        STNode_true(const Node& _node, const Update& _update)
            : node(_node), update(_update), l(nullptr), r(nullptr) {}
    };
    using STNode =
        typename std::conditional<is_lazy, STNode_true, STNode_false>::type;
    int pid;
    ll N;
    ptr<STNode> nil;
    vector<ptr<STNode>> roots;

    explicit PersistentSegTree(const std::vector<Node>& v, const Node& _id_node,
                               const CombineNodes& _combine,
                               const Update& _id_update,
                               const ApplyUpdate& _apply_update,
                               const ComposeUpdates& _compose_updates = nullptr)
        : N(int(v.size())),
          pid(0),
          nil(nullptr),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        nil = my_new(id_node);
        nil->l = nil->r = nil;
        if constexpr (RESERVE_ROOTS) roots.reserve(1'100'000);
        roots.push_back(build(v));
    }

    explicit PersistentSegTree(const ll& _N, const Node& _id_node,
                               const CombineNodes& _combine,
                               const Update& _id_update,
                               const ApplyUpdate& _apply_update,
                               const ComposeUpdates& _compose_updates = nullptr)
        : N(_N),
          pid(0),
          nil(nullptr),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        nil = my_new(id_node);
        nil->l = nil->r = nil;
        if constexpr (RESERVE_ROOTS) roots.reserve(1'100'000);
        roots.push_back(nil);
    }

    ptr<STNode> my_new(const Node& node) {
        ptr<STNode> ans = new STNode;
        ans->node = node;
        if constexpr (is_lazy) ans->update = id_update;
        ans->l = ans->r = nil;
        return ans;
    }
    ptr<STNode> merge(ptr<STNode> l, ptr<STNode> r) {
        ptr<STNode> ans = new STNode;
        ans->node = combine(l->node, r->node);
        if constexpr (is_lazy) ans->update = id_update;
        ans->l = l;
        ans->r = r;
        return ans;
    }
    ptr<STNode> build(const vector<Node>& v) {
        N = (ll)v.size();
        return build(0, (ll)v.size(), v);
    }
    ptr<STNode> build(ll l, ll r, const vector<Node>& v) {
        if (l + 1 == r) return my_new(v[l]);
        ll m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

   private:
    ptr<STNode> new_lazy_child(ptr<STNode> n, const Update& u) {
        ptr<STNode> ans = new STNode;
        ans->node = apply_update(u, n->node);
        ans->l = n->l;
        ans->r = n->r;
        if constexpr (is_lazy) ans->update = compose_updates(u, n->update);
        return ans;
    }
    void pushdown_(ptr<STNode> n) {
        if constexpr (is_lazy) {
            if (n->update == id_update) return;
            n->l = new_lazy_child(n->l, n->update);
            n->r = new_lazy_child(n->r, n->update);
            n->update = id_update;
        }
    }
    ptr<STNode> update_(ll a, const Update& x, ptr<STNode> n, ll l, ll r) {
        if (l + 1 == r) return my_new(apply_update(x, n->node));
        ll m = (l + r) >> 1;
        if constexpr (is_lazy) pushdown_(n);
        if (a < m) return merge(update_(a, x, n->l, l, m), n->r);
        return merge(n->l, update_(a, x, n->r, m, r));
    }
    Node query_(ll a, ll b, ptr<STNode> n, ll l, ll r) {
        if (n == nil or r <= a or b <= l)
            return id_node;  // nullptr never possible
        if (a <= l and r <= b) return n->node;
        ll m = (l + r) >> 1;
        if constexpr (is_lazy) pushdown_(n);
        return combine(query_(a, b, n->l, l, m), query_(a, b, n->r, m, r));
    }
    ptr<STNode> update_(ll L, ll R, const Update& x, ptr<STNode> n, ll l,
                        ll r) {
        if (L <= l and r <= R) return my_new(apply_update(x, n->node));
        ll m = (l + r) >> 1;
        if constexpr (is_lazy) pushdown_(n);
        ptr<STNode> left = n->l;
        ptr<STNode> right = n->r;
        if (L < m) left = update_(L, R, x, n->l, l, m);
        if (m < R) right = update_(L, R, x, n->r, m, r);
        return merge(left, right);
    }

   public:
    ptr<STNode> update(ptr<STNode> n, ll k, const Update& x) {
        ptr<STNode> root = update_(k, x, n, 0, N);
        roots.push_back(root);
        return root;
    }
    ptr<STNode> update(int t, ll k, const Update& x) {
        ptr<STNode> root = update_(k, x, roots[t], 0, N);
        roots.push_back(root);
        return root;
    }
    ptr<STNode> update(ptr<STNode> n, ll a, ll b, const Update& x) {
        assert(0 <= a && a < b && b <= N);
        ptr<STNode> root = update_(a, b, x, n, 0, N);
        roots.push_back(root);
        return root;
    }
    ptr<STNode> update(int t, ll a, ll b, const Update& x) {
        assert(0 <= a && a < b && b <= N);
        ptr<STNode> root = update_(a, b, x, roots[t], 0, N);
        roots.push_back(root);
        return root;
    }
    ptr<STNode> update_last(ll k, const Update& x) {
        ptr<STNode> root = update_(k, x, roots.back(), 0, N);
        roots.push_back(root);
        return root;
    }
    ptr<STNode> update_last(ll a, ll b, const Update& x) {
        assert(0 <= a && a < b && b <= N);
        ptr<STNode> root = update_(a, b, x, roots.back(), 0, N);
        roots.push_back(root);
        return root;
    }

    Node query(ptr<STNode> n, ll a, ll b) {
        assert(0 <= a && a < b && b <= N);
        return query_(a, b, n, 0, N);
    }
    Node query(int t, ll a, ll b) {
        assert(0 <= a && a < b && b <= N);
        return query_(a, b, roots[t], 0, N);
    }
    Node query_last(ll a, ll b) {
        assert(0 <= a && a < b && b <= N);
        return query_(a, b, roots.back(), 0, N);
    }
    ptr<STNode> new_tree() { return nil; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;

        vector<int> left(n);
        map<int, int> last;
        for (int i = 0; i < n; i++) {
            if (!last.count(a[i]))
                left[i] = -1;
            else
                left[i] = last[a[i]];
            last[a[i]] = i;
        }

        const int inf = 1e9;
        struct Node {
            int max_prev_idx;
            int max_prev_at;
        };
        const Node id_node{inf, inf};
        const auto combine = [](const Node& a, const Node& b) -> Node {
            if (a.max_prev_idx < b.max_prev_idx)
                return a;
            else
                return b;
        };
        using Update = pair<int, int>;
        const Update id_update = {-1, -1};
        const auto apply_update = [&id_update](const Update& u, const Node& n) {
            if (u == id_update) return n;
            return Node{u.first, u.second};
        };
        const auto compose_updates = [&id_update](const Update& u,
                                                  const Update& v) {
            if (u == id_update) return v;
            return u;
        };

        //  PersistentSegTree st(n, id_node, combine, id_update, apply_update,
        //                       compose_updates);

        PersistentSegTree st(vector<Node>(n, id_node), id_node, combine,
                             id_update, apply_update);

        vector<ptr<decltype(st)::STNode>> roots(n + 1);
        roots[0] = st.roots[0];
        for (int i = 0; i < n; ++i) {
            if (left[i] != -1) st.update_last(left[i], Update{inf, inf});
            roots[i + 1] = st.update_last(i, Update{left[i], i});
        }

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            --l;
            auto [ans, ans_idx] = st.query(roots[r], l, r);
            if (ans < l)
                cout << a[ans_idx] << '\n';
            else
                cout << 0 << '\n';
        }
    }
}

