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

    int a[n] = {0}, freq[n + 1] = {0}, ans[n];
    ans[0] = 1, ans[n - 1] = 0;

    for (auto &x : a) {
        cin >> x;
        freq[--x]++;
        ans[n - 1] |= !x;
    }

    for (int i = 0; i < n; ++i) ans[0] &= (freq[i] == 1);

    int l = 0, r = n - 1, id = n, curmin = 0;

    for (int i = 0; i < n; ++i) {
        if (a[l] == i) freq[a[l++]]--;
        else if (a[r] == i) freq[a[r--]]--;
        else {
            id = i;
            break;
        }
        if (freq[i] || !freq[i + 1]) {
            id = i;
            break;
        }
    }

    for (int i = 1; i < n - 1; ++i) ans[i] = (i >= n - id - 1);
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


