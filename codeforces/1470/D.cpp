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

const int maxn = 1'000'001;
vector<int> sqfree(maxn, 1);
vector<int> prime(maxn, 1);

void precompute() {
    sqfree[0] = 0;
    sqfree[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (prime[i]) {
            sqfree[i] = i;
            for (int j = i << 1; j < maxn; j += i) {
                prime[j] = 0;
                int k = j, c = 0;
                while (k % i == 0) c++, k /= i;
                if (c & 1) sqfree[j] *= i;
            }
        }
    }
}

void solve(int) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector<int> col(n, -1);
    
    function<void(int)> dfs = [&] (int u) {
        bool c = 1;
        for (auto v : g[u]) {
            if (col[v] == 1) c = 0;
        }
        col[u] = c;
        for (auto v : g[u]) {
            if (col[v] == -1) dfs(v);
        }
    };

    dfs(0);

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (col[i] == -1) {
            cout << "NO\n";
            return;
        }
        if (col[i] == 1) ans.push_back(i + 1);
    }

    cout << "YES\n";
    
    cout << ans.size() << '\n';
    for (auto &x : ans) cout << x << ' ';
    cout << '\n';
}

void brute(int) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a) cin >> x, x--;
    vector<int> c(m);
    for (auto &x : c) cin >> x;
    sort(begin(a), end(a));
    int cur = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if (cur <= a[i]) {
            ans += a[cur];
            cur++;
        } else {
            ans += c[a[i]];
        }
    }
    cout << ans << '\n';
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
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

