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
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    while (q--) {
        int typ;
        cin >> typ;
        if (typ == 1) {
            int pos, val;
            cin >> pos >> val;
            a[pos] = val;
        } else {
            long long x, k;
            cin >> x >> k;
            long long residue = 0, big = 0, oldx = x;
            for (int i = 0; i <= x; ++i) {
                residue += a[i] * ((1LL << i) - 1);
                k -= a[i];
            }
            if (k <= 0) {
                cout << 0 << '\n';
            } else {
                for (++x; x < n; ++x) {
                    long long add = (1LL << (x - oldx));
                    long long req = min(k / add, a[x]);
                    big += req * (add - 1);
                    k -= req * add;
                    residue += req * add * ((1LL << oldx) - 1);
                    if (req != a[x]) break;
                }
                if (k <= 0) {
                    cout << big << '\n';
                } else if (x >= n) {
                    if (k > residue) cout << -1 << '\n';
                    else cout << big + k << '\n';
                } else {
                    long long ans = 2e18;
                    while (x > oldx) {
                        if (residue >= k) {
                            ans = min(ans, big + k);
                        }
                        ++big;
                        --x;
                        long long add = 1LL << (x - oldx);
                        if (k >= add) {
                            big += add - 1;
                            k -= add;
                            residue += add * ((1LL << oldx) - 1);
                        }
                    }
                    cout << min(ans, big) << '\n';
                }
            }
        }
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

