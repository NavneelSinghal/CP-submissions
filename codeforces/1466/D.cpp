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

void precompute() {

}

void solve(int _) {
    
    int n;
    cin >> n;
    
    vector<int> w(n), d(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        ++d[u], ++d[v];
    }

    long long ans = 0;
    
    vector<int> add(n - 2);
    
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        ans += w[i];
        while (--d[i]) {
            add[cur++] = w[i];
        }
    }
    
    sort(add.rbegin(), add.rend());

    cout << ans << ' ';
    for (auto &x : add) {
        ans += x;
        cout << ans << ' ';
    }
    cout << '\n';


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
