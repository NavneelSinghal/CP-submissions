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

string a;

void solve(int _) {

    int n, k;
    cin >> n >> k;
    cin >> a;
    
    int w = min(__lg(n) + 1, k);
    
    vector<int> vis(1 << w, 0);
    
    int s = k - w;
    int cur = 0, cnt = 0;

    for (int i = 0; i < s; ++i) {
        cnt += a[i] == '1';
    }

    for (int i = s; i < k - 1; ++i) {
        cur = (cur << 1) | (a[i] == '1');
    }

    int mask = (1 << w) - 1;

    for (int i = k - 1; i < n; ++i) {
        cur = mask & ((cur << 1) | (a[i] == '1'));
        if (cnt == s) vis[cur ^ mask] = 1;
        cnt += a[i - w + 1] - a[i - k + 1];
    }

    int ans = 0;
    for (; ans <= mask && vis[ans]; ++ans);
    
    if (ans == mask + 1) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    string fin(k, '0');
    for (int i = 0; i < s; ++i) fin[i] = '0';
    vector<int> bin;
    for (int i = 0; i < w; ++i) {
        fin[k - i - 1] = '0' + (ans & 1);
        ans >>= 1;
    }
    assert(fin.size() == k);
    cout << fin << '\n';
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
