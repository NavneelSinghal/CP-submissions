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

inline int hash_string(string& a) {
    int ans = 0;
    for (auto &x : a) {
        if (x == '_') {
            ans = ans * 27 + 26;
        } else {
            ans = ans * 27 + x - 'a';
        }
    }
    return ans;
}

void solve(int) {
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<string> a(n);
    for (auto &x : a) cin >> x;
    
    vector<int> position(600'000, -1);
    for (int i = 0; i < n; ++i)
        position[hash_string(a[i])] = i;

    vector<vector<int>> g(n);
    vector<int> cnt(n);

    for (int i = 0; i < m; ++i) {
    
        string x;
        int mt;
        cin >> x >> mt;
        --mt;
        
        bool works = false;

        for (int j = 0; j < (1 << k); ++j) {
        
            string w = x;
            for (int l = 0; l < k; ++l)
                if ((j >> l) & 1)
                    w[l] = '_';
            
            int pos = position[hash_string(w)];
            if (~pos) {
                if (mt == pos) {
                    works = true;
                } else {
                    g[mt].push_back(pos);
                    cnt[pos]++;
                }
            }
        }

        if (!works) {
            cout << "NO\n";
            return;
        }
    }

    vector<int> q(n);
    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        if (!cnt[i]) {
            q[r++] = i;
        }
    }

    while (l < r) {
        for (auto v : g[q[l++]]) {
            --cnt[v];
            if (!cnt[v]) {
                q[r++] = v;
            }
        }
    }

    if (r < n) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (auto x : q) cout << x + 1 << ' ';
    cout << '\n';

}

void brute(int) {
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
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

