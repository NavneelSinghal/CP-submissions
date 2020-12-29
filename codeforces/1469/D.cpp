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

bool intersects(int a, int b, int c, int d) {
    return max(a, c) <= min(b, d);
}

void solve(int _) {
    int n;
    cin >> n;
    vector<pair<int, int>> ans;
    function<void(int, vector<pair<int, int>>&)> rec = [&] (int n, vector<pair<int, int>> &ans) {
        if (n <= 2) return;
        int sq = max(1, (int)sqrt(n) - 3);
        while (sq < (n + sq - 1) / sq) ++sq;
        for (int i = sq + 1; i < n; ++i) {
            ans.emplace_back(i, n);
        }
        for (int i = 0; i < 2; ++i) {
            ans.emplace_back(n, sq);
        }
        rec(sq, ans);
    };
    rec(n, ans);
    cout << ans.size() << '\n';
    for (auto &[x, y] : ans) cout << x << ' ' << y << '\n';
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
