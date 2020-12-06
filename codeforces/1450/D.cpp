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

template<typename T>
struct sparse_table {
    int n, l;
    vector<vector<T>> s;
    sparse_table(vector<T>& a) {
        n = a.size();
        l = 2 + __lg(n + 1);
        s.assign(l, vector<T>(n));
        s[0] = a;
        for (int j = 0; j < l - 1; ++j) {
            for (int i = 0; i + (2 << j) <= n; ++i) {
                s[j + 1][i] = min(s[j][i], s[j][i + (1 << j)]);
            }
        }
    }
    // [l, r)
    T query(int l, int r) {
        int sz = __lg(r - l);
        return min(s[sz][l], s[sz][r - (1 << sz)]);
    }
};

void solve(int _) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x, --x;
    sparse_table<int> s(a);
    int l = 0, r = n - 1;
    int fail = -1;
    for (int i = 0; i < n; ++i) {
        if (a[l] == i) {
            l++;
        } else if (a[r] == i) {
            r--;
        } else {
            fail = i;
            break;
        }
        if (s.query(l, r + 1) != i + 1) {
            fail = i;
            break;
        }
    }
    vector<int> ans(n);
    sort(a.begin(), a.end());
    ans[0] = 1;
    for (int i = 0; i < n; ++i) {
        ans[0] &= (a[i] == i);
    }
    for (int i = 1; i < n; ++i) {
        ans[i] = (i >= n - fail - 1);
    }
    ans[n - 1] = a[0] == 0;
    for (auto &x : ans) cout << x;
    cout << '\n';
}

signed main() {
    setIO();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}


