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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, mod));
    for (int i = 0; i < m; ++i) {
        int u, v, x;
        cin >> u >> v >> x;
        g[--u][--v] = x;
        g[v][u] = -x;
    }
    // bipartite
    vector<int> col(n, -1);
    queue<int> q;
    col[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (g[u][v] != mod) {
                if (col[u] == col[v]) {
                    cout << "NO\n";
                    return;
                }
                if (col[v] == -1) {
                    col[v] = col[u] ^ 1;
                    q.push(v);
                }
            }
        }
    }

    vector<vector<int>> d(n, vector<int>(n, mod));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (int i = 0; i < n; ++i) {
        if (!col[i]) for (int j = 0; j < n; ++j) if (g[i][j] != mod) {
            if (g[i][j] == 1) {
                d[i][j] = 0;
                d[j][i] = 0;
            } else if (g[i][j] == -1) {
                d[i][j] = -1;
                d[j][i] = 1;
            } else {
                d[i][j] = 0;
                d[j][i] = 1;
            }
        }
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    vector<int> ans;
    int cost = -1;

    for (int i = 0; i < n; ++i) {
        if (d[i][i] < 0) {
            ans = vector<int>();
            cost = -1;
            break;
        }
        vector<int> cur(n);
        int val = 0;
        for (int j = 0; j < n; ++j) cur[j] = (d[i][j] << 1) + col[j];
        for (int j = 0; j < n; ++j) {
            if (cur[j] < cur[i]) {
                val = -1;
                break;
            }
            val = max(val, cur[j] - cur[i]);
        }
        if (val > cost) {
            cost = val, ans = cur;
        }
    }

    if (cost == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << cost << '\n';
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
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


