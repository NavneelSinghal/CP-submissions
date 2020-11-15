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
    if (name.size() == 0)
        return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    cout << setprecision(10) << fixed;
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

struct Fenwick {
    int n;
    vector<int> t;
    Fenwick(int n) : n(n), t(n + 1) {}

    // prefix_sum[0..i]
    int query(int i) {
        int s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }

    // increase a[i] by v
    void update(int v, int i) {
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }
};

void solve(int case_no) {

    int n;
    string s;
    
    cin >> n >> s;
    
    vector<vector<int>> loc(26), rev_loc(26);
    
    for (int i = 0; i < n; ++i) {
        loc[s[i] - 'a'].push_back(i);
    }
    
    for (int i = 0; i < n; ++i) {
        rev_loc[s[i] - 'a'].push_back(n - i - 1);
    }
    
    vector<int> p(n);
    for (int i = 0; i < 26; ++i) {
        int z = loc[i].size();
        for (int j = 0; j < z; ++j) {
            p[loc[i][j]] = rev_loc[i][z - 1 - j];
        }
    }

    // number of inversions in p
    
    Fenwick ft(n);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += i - ft.query(p[i]);
        ft.update(1, p[i] + 1);
    }

    cout << ans << '\n';

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

