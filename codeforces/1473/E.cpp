#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename X, typename Y>
X &remin(X &x, const Y &y) {
    return x = (y < x) ? y : x;
}

template <typename X, typename Y>
X &remax(X &x, const Y &y) {
    return x = (x < y) ? y : x;
}

template <typename X, typename Y>
bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
}

const int mod = 998244353;
// const int mod = 1e9 + 7;
const long long linf = 3e18;

long long pwr_mod(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, long long n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

int merge_ranges(int a, int b, int c, int d) {
    assert(a <= b);
    assert(c <= d);
    if (c < a) {
        swap(a, c);
        swap(b, d);
    }
    // a <= c
    if (b < c) {
        return b - a + 1 + d - c + 1;
    } else {
        return max(b, d) - a + 1;
    }
}

void solve(int _) {
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, long long>>> g(n);
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    const long long INF = 1e18;
    vector<long long> d(n * 4, INF);
    vector<bool> vis(n * 4);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    pq.emplace(0, 0);
    while (!pq.empty()) {
        long long dist;
        int v;
        tie(dist, v) = pq.top();
        pq.pop();
        if (vis[v]) continue;
        vis[v] = true;
        d[v] = dist;
        int mask = v / n;
        for (auto &e : g[v % n]) {
            long long w;
            int u;
            tie(u, w) = e;
            if (~mask >> 1 & 1)
                pq.emplace(dist, (mask | 2) * n + u);
            pq.emplace(dist + w, mask * n + u);
            pq.emplace(dist + 2 * w, (mask | 1) * n + u);
        }
    }
    for (int i = 1; i < n; ++i) {
        cout << min({d[i], d[n + i], d[3 * n + i]}) << ' ';
    }
    cout << '\n';
}

void brute(int _) {
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}


/* stuff you should look for
	* int overflow, array bounds
	* special cases (n = 1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
