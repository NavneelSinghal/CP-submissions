#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    cout << setprecision(10) << fixed;
}

void solve(int case_no) {
    
    int n, x;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        ans = __gcd(ans, x);
    }
    cout << ans << '\n';

    return;
}

signed main() {
    setIO();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        solve(_t);
    }
    return 0;
}
