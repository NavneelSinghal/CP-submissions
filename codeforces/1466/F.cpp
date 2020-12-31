#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0)
        return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
}

// const int mod = 998244353;
const int mod = 1e9 + 7;

template <typename T>
T pwr(T a, long long n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {

}

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

vector<int32_t> par, siz;

void make_set(int32_t v) {
    par[v] = v;
    siz[v] = 1;
}

int32_t find_set(int32_t v) {
    if (v == par[v]) return v;
    return par[v] = find_set(par[v]);
}

bool union_sets(int32_t a, int32_t b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
    }
    return a != b;
}

void solve(int _) {
    
    int n, m;
    cin >> n >> m;

    par.resize(m + 1);
    siz.resize(m + 1);

    for (int i = 0; i <= m; ++i) {
        make_set(i);
    }

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        int u, v;
        if (k == 1) {
            cin >> u;
            --u;
            v = m;
        } else {
            cin >> u >> v;
            --u, --v;
        }
        if (union_sets(u, v)) {
            ans.push_back(i + 1);
        }
    }

    mint answer = pwr(mint(2), (int) ans.size());

    cout << answer << ' ' << ans.size() << '\n';

    for (auto i : ans) cout << i << ' ';
    cout << '\n';

}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
