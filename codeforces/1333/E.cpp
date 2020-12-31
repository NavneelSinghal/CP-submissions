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
    if (n < 3) {
        cout << -1 << '\n';
        return;
    }
    int a[n][n];
    int t[] = {9, 5, 6, 7, 2, 8, 1, 3, 4};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            a[i][j] = n * n - 3 * 3 + t[i * 3 + j];
        }
    }
    auto nxt = [&] (int i, int j) {
        if (i < 3 && j < 3) return make_pair(-1, -1);
        int ii = i, jj = j;
        int pi = i & 1, pj = j & 1, l = i < j, le = i <= j;
        if (l && pj) ++ii;
        else if ((le && !pj && i != 0) || (j == 0 && pi)) --ii;
        if (!le && !pi) ++jj;
        else if ((!l && pi && j != 0) || (i == 0 && !pj)) --jj;
        return make_pair(ii, jj);
    };
    int i, j;
    if (n & 1) {
        i = n - 1, j = 0;
    } else {
        j = n - 1, i = 0;
    }
    int cur = 1;
    while (i >= 0) {
        a[i][j] = cur++;
        tie(i, j) = nxt(i, j);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
