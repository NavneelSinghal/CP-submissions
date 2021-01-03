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

    vector<vector<int>> a(m, vector<int>(n));
    
    for (auto &v : a) {
        for (auto &x : v) {
            cin >> x;
            --x;
        }
    }
    
    vector<int> loc(n);
    for (int i = 0; i < n; ++i) {
        loc[a[0][i]] = i;
    }
    
    for (auto &v : a) {
        for (auto &x : v) {
            x = loc[x];
        }
    }
    
    vector<int> len(n, n - 1);
    
    for (auto &v : a) {
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (cur < i) ++cur;
            while (cur + 1 < n && v[cur + 1] == v[cur] + 1) ++cur;
            len[v[i]] = min(len[v[i]], v[cur]);
        }
    }
    
    long long ans = 0, cur = 0;
    
    while (cur < n) {
        long long w = len[cur] - cur + 1;
        ans += w * (w + 1) / 2;
        cur = len[cur] + 1;
    }
    
    cout << ans << '\n';
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
