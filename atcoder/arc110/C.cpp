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

long long w = 1e10;

void solve(int _) {
    int n;
    cin >> n;
    vector<int> a(n), pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[--a[i]] = i;
    }
    vector<int> order, done(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        if (done[i]) {
            if (a[i] != i) {
                cout << -1 << '\n';
                return;
            }
        } else {
            for (int j = pos[i] - 1; j >= i; --j) {
                swap(a[j], a[j + 1]);
                order.push_back(j + 1);
                done[j] = 1;
            }
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        if (!done[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    for (auto x : order) {
        cout << x << '\n';
    }
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


