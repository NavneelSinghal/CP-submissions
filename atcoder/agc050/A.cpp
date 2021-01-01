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

long long pwr(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

template<typename X, typename Y> 
X& remin(X& x, const Y& y) { return x = (y < x) ? y : x; }

template<typename X, typename Y>
X& remax(X& x, const Y& y) { return x = (x < y) ? y : x; }

template<typename X, typename Y>
bool ckmin(X& x, const Y& y) { return (y < x) ? (x = y, 1) : 0; }

template<typename X, typename Y>
bool ckmax(X& x, const Y& y) { return (x < y) ? (x = y, 1) : 0; }

void precompute() {
}

void solve(int _) {

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cout << (2 * i - 1) % n + 1 << ' ' << (2 * i) % n + 1 << '\n';
    }

}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
