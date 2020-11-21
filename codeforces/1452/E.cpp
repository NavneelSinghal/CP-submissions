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
//const int mod = 1e9 + 7;

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
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> a(m);
    for (auto &[x, y] : a) {
        cin >> x >> y;
        --x;
    }
    sort(a.begin(), a.end(), [](const pair<int, int> &a, const pair<int, int> &b) { return a.first + a.second < b.first + b.second; });
    vector<int> suf(m + 1);
    for (int i = k; i <= n; ++i) {
        int cur = 0;
        for (int j = m - 1; ~j; --j) {
            cur += max(0, min(i, a[j].second) - max(i - k, a[j].first));
            suf[j] = max(suf[j], cur);
        }
    }
    int ans = suf[0];
    for (int i = k; i <= n; ++i) {
        int cur = 0;
        for (int j = 0; j < m; ++j) {
            cur += max(0, min(i, a[j].second) - max(i - k, a[j].first));
            ans = max(ans, cur + suf[j + 1]);
        }
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

