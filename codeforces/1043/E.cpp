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
bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
}

const int mod = 998244353;
// const int mod = 1e9 + 7;
const long long linf = 3e18;

long long pwr_mod(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, long long n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

void solve(int _) {

    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> g(n);
    vector<int> d(n);
    vector<long long> x(n), y(n);

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        d[i] = i;
    }

    sort(d.begin(), d.end(), [&] (int i, int j) {return y[i] - x[i] < y[j] - x[j];});
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<long long> pre_y(n + 1), suf_x(n + 1);

    for (int i = 0; i < n; ++i) {
        pre_y[i + 1] = pre_y[i] + y[d[i]];
    }

    for (int i = n - 1; i >= 0; --i) {
        suf_x[i] = suf_x[i + 1] + x[d[i]];
    }

    vector<long long> a(n);

    for (int i = 0; i < n; ++i) {
        
        int w = d[i];
        
        a[w] = pre_y[i] + suf_x[i + 1] + i * x[w] + (n - 1 - i) * y[w];
        
        for (auto v : g[w]) {
            a[w] -= min(x[w] + y[v], x[v] + y[w]);
        }
    }

    for (auto v : a) cout << v << ' ';
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
