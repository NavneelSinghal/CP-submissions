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

const int mod = 998244353;

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
    int n, w;
    cin >> n >> w;
    map<int, vector<int>> events;
    for (int i = 0; i < n; ++i) {
        int s, t, p;
        cin >> s >> t >> p;
        events[s].push_back(p);
        events[t].push_back(-p);
    }
    long long cur = 0;
    for (auto &[x, y] : events) {
        for (auto r : y) {
            cur += r;
        }
        if (cur > w) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    return;
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

