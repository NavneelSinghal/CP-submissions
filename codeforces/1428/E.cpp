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

const int mod = 998244353;

long long pwr(long long a, int n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

int64_t value(int64_t a, int64_t n) {
    int64_t e = a / n;
    int64_t r = a - n * e;
    return (n - r) * e * e + r * (e + 1) * (e + 1);
}

void solve(int _) {
    
    int n, k;
    int64_t a, b, ans = 0;
    priority_queue<pair<int64_t, pair<int64_t, int64_t>>> pq;
    
    cin >> n >> k;
    
    for (int i = 0; i < n; ++i) {
        cin >> a;
        ans += a * a;
        pq.push({value(a, 1) - value(a, 2), {a, 2}});
    }

    for (int i = n; i < k; ++i) {
        ans -= pq.top().first;
        tie(a, b) = pq.top().second;
        pq.pop();
        pq.push({value(a, b) - value(a, b + 1), {a, b + 1}});
    }
    
    cout << ans << '\n';
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

