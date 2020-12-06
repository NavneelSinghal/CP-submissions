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
    vector<int> a(n), freq(n + 1);
    for (auto &x : a) cin >> x, freq[x]++;
    if (*max_element(freq.begin(), freq.end()) > (n + 1) / 2) {
        cout << -1 << '\n';
    } else {
        for (auto &x : freq) x = 0;
        int cnt = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i - 1]) {
                ++cnt;
                freq[a[i - 1]]++;
                freq[a[i]]++;
            }
        }
        freq[a[0]]++;
        freq[a[n - 1]]++;
        cout << max(cnt, *max_element(freq.begin(), freq.end()) - 2) << '\n';
    }
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


