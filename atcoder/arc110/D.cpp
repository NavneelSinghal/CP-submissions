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

//const int mod = 998244353;
const int mod = 1e9 + 7;

long long pwr(long long a, int n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

long long w = 1e10;

void solve(int _) {
    int n, m, x, s;
    cin >> n >> m;
    s = n, m += n;
    while (n--) {
        cin >> x;
        s += x;
    }
    n = s + 100;
    vector<int> fact(n), ifact(n);
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < n; ++i) {
        fact[i] = (long long) fact[i - 1] * i % mod;
    }
    ifact[n - 1] = pwr(fact[n - 1], mod - 2);
    for (int i = n - 2; i >= 1; --i) {
        ifact[i] = (long long) ifact[i + 1] * (i + 1) % mod;
    }
    // inv[i] = (long long) ifact[i] * fact[i] % mod
    long long ans = 1;
    for (int i = 1; i <= s; ++i, --m) {
        ans = (ans * m % mod) * ((long long) ifact[i] * fact[i - 1] % mod) % mod;
    }
    cout << ans << '\n';
}

signed main() {
    setIO();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}


