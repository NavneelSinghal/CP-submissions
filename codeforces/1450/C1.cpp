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
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto &x : a) cin >> x;
    int already[3][2] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '.') continue;
            already[(i + j) % 3][a[i][j] == 'X']++;
        }
    }
    int chosenX = -1, chosenY = -1, mn = 1e9;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;
            int toChange = already[i][1] + already[j][0];
            if (toChange < mn) {
                mn = toChange;
                chosenX = i;
                chosenY = j;
            }
        }
    }
    // change colour i to x and j to o
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '.') continue;
            int col = (i + j) % 3;
            if (col == chosenX) {
                a[i][j] = 'O';
            }
            if (col == chosenY) {
                a[i][j] = 'X';
            }
        }
    }
    for (auto &x : a) cout << x << '\n';
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

 