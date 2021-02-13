#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename X, typename Y>
X &remin(X &x, const Y &y) {
    return x = (y < x) ? y : x;
}

template <typename X, typename Y>
X &remax(X &x, const Y &y) {
    return x = (x < y) ? y : x;
}

template <typename X, typename Y>
[[nodiscard]] bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
[[nodiscard]] bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

template <typename T> void ignore_unused(const T&) {}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, int64_t n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

// modular int library

template <int32_t MOD = 998'244'353>
struct Modular {
    int32_t value;
    static const int32_t MOD_value = MOD;

    Modular(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }
    Modular(long long a, long long b) : value(0) {
        *this += a;
        *this /= b;
    }

    Modular& operator+=(Modular const& b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    Modular& operator-=(Modular const& b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }
    Modular& operator*=(Modular const& b) {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend Modular mexp(Modular a, long long e) {
        Modular res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

    Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, Modular const& a) {
        return os << a.value;
    }
    friend bool operator==(Modular const& a, Modular const& b) {
        return a.value == b.value;
    }
    friend bool operator!=(Modular const& a, Modular const& b) {
        return a.value != b.value;
    }
};

using mint = Modular<mod>;

void precompute() {
}

const int N = 200100;

struct node {
    // heads = number of 1, lazy = what we need to assign, -1 if none
    int heads, lazy;
    node() { heads = 0, lazy = -1; }
    node(int h, int l) {heads = h, lazy = l;}
};

// how to combine two nodes
node merge(node& a, node& b) {
    node x;
    x.heads = a.heads + b.heads;
    return x;
}

// how to update a given node
void assign(node& a, int l, int r, int val) {
    a.heads = (r - l + 1) * val;
    a.lazy = val;
}

node t[4 * N];

void push(int v, int tl, int tm, int tr) {
    if (t[v].lazy >= 0) {
        assign(t[v << 1], tl, tm, t[v].lazy);
        assign(t[v << 1 | 1], tm + 1, tr, t[v].lazy);
    }
    t[v].lazy = -1;
}

void build(int v, int l, int r, string& a) {
    if (l == r) {
        t[v] = node(a[l] - '0', -1);
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid, a);
    build((v << 1) | 1, mid + 1, r, a);
    t[v] = merge(t[(v << 1)], t[(v << 1) | 1]);
}

void update(int v, int tl, int tr, int l, int r, int val) {
    if (l > r) return;
    if (l == tl && r == tr) {
        assign(t[v], tl, tr, val);
        return;
    }
    int tm = (tl + tr) >> 1;
    push(v, tl, tm, tr);
    update(v << 1, tl, tm, l, min(r, tm), val);
    update(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val);
    t[v] = merge(t[v << 1], t[v << 1 | 1]);
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l <= tl && tr <= r) return t[v].heads;
    int tm = (tl + tr) >> 1;
    push(v, tl, tm, tr);
    return query(v << 1, tl, tm, l, min(r, tm)) +
           query(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
}

void solve(int) {
    
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    string f;
    cin >> f;
    
    vector<pair<int, int>> v(q);
    for (auto &[x, y] : v) {
        cin >> x >> y;
        --x, --y;
    }
    
    build(1, 0, n - 1, f);
    
    for (int i = q - 1; i >= 0; --i) {
        int l = v[i].first;
        int r = v[i].second;
        int s = query(1, 0, n - 1, l, r);
        if (2 * s == r - l + 1) {
            cout << "NO\n";
            return;
        } else if (2 * s < r - l + 1) {
            update(1, 0, n - 1, l, r, 0);
        } else {
            update(1, 0, n - 1, l, r, 1);
        }
    }
    
    string ss;
    for (int i = 0; i < n; ++i) {
        ss += '0' + query(1, 0, n - 1, i, i);
    }
    
    if (ss == s) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

void brute(int) {
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        //brute(_t);
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
