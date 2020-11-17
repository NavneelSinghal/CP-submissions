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

void solve(int _) {
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    
    function<int(vector<int>&, int)> f = [&] (vector<int>& a, int depth) {
        if (depth < 0) return 0;
        vector<int> aa[2];
        for (auto x : a) aa[(x >> depth) & 1].push_back(x);
        for (auto i : {0, 1}) if (aa[i].empty()) return f(aa[i ^ 1], depth - 1);
        return 1 + max(f(aa[0], depth - 1), f(aa[1], depth - 1));
    };

    cout << n - 1 - f(a, 30) << '\n';
}

signed main() {
    setIO();
    int t = 1;
    //cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}

