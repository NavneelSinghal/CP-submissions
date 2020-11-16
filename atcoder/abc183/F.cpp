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

//const int mod = 998244353;
const int mod = 1e9 + 7;

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
    
    int c[n];
    for (int i = 0; i < n; ++i) cin >> c[i];
    
    int r[n]; // r[i] = representative of i
    iota(r, r + n, 0);

    map<int, vector<int>> rep[n]; // rep[i] contains a map from class to vector of elements in the class
    int sz[n];

    for (int i = 0; i < n; ++i) {
        rep[i][c[i]].push_back(i);
        sz[i] = 1;
    }

    while (q--) {

        int typ;
        cin >> typ;
        
        if (typ == 1) {
            
            int a, b;
            cin >> a >> b;
            --a, --b;

            int ra = r[a];
            int rb = r[b];
            
            if (ra == rb) continue;
            if (sz[ra] < sz[rb]) {
                swap(ra, rb);
                swap(a, b);
            }

            auto &m = rep[ra];
            for (auto &[cl, el] : rep[rb]) {
                auto &v = m[cl];
                for (auto e : el) {
                    v.push_back(e);
                    r[e] = ra;
                }
            }

            sz[ra] += sz[rb];
            sz[rb] = 0;

            rep[rb].clear();

        } else {

            int x, y;
            cin >> x >> y;
            --x;

            int rx = r[x];
            cout << rep[rx][y].size() << '\n';

        }
    }

    return;
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

