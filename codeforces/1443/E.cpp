#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

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

    int n, q;
    cin >> n >> q;
    
    long long a[n];
    iota(a, a + n, 1LL);

    const int INV_FACT = 14;
    long long fact[INV_FACT];
    
    fact[0] = 1;
    for (int i = 1; i < INV_FACT; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    long long x = 0, old_x;
    int lft = max(0, n - INV_FACT), iter = min(n, INV_FACT);

    while (q--) {
        
        int typ;
        cin >> typ;
        
        if (typ == 1) {

            int position = lft;
            vector<int> pos(iter);
            iota(pos.begin(), pos.end(), 1);
            old_x = x;
            for (int i = iter - 1; ~i; --i) {
                long long w = x / fact[i];
                x %= fact[i];
                a[position++] = pos[w] + lft;
                pos.erase(pos.begin() + w);
            }
            x = old_x;
            
            int l, r;
            cin >> l >> r;
            --l;
            
            assert(l >= 0 && l < r && r <= n);

            long long ans = 0;
            if (l >= lft) {
                for (int i = l; i < r; ++i) ans += a[i];
            } else if (r <= lft) {
                ans = (1LL * l + r + 1) * (r - l) / 2; 
            } else {
                ans = (1LL * l + lft + 1) * (lft - l) / 2;
                for (int i = lft; i < r; ++i) ans += a[i];
            }
            cout << ans << '\n';

        } else {

            int y;
            cin >> y;
            x += y;

        }
    }
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

