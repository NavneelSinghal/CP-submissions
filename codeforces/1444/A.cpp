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

void solve(int case_no) {
    long long p, q;
    cin >> p >> q;
    
    long long ans = 0, qq = q;
    for (int i = 2; i * i <= q; ++i) {
        if (q % i == 0) {
            while (q % i == 0) q /= i;
            long long pp = p;
            while (pp % qq == 0) pp /= i;
            ans = max(ans, pp);
        }
    }
    
    if (q > 1) {
        long long pp = p;
        while (pp % qq == 0) pp /= q;
        ans = max(ans, pp);
    }

    cout << ans << '\n';
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

