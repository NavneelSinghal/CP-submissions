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

const int N = 1e5 + 10, M = N - 2;

int t[N << 2], last[N << 1], works[N << 2];

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = val;
        return;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) update(v << 1, tl, tm, pos, val);
    else update(v << 1 | 1, tm + 1, tr, pos, val);
    t[v] = min(t[v << 1], t[v << 1 | 1]);
}

int find(int v, int tl, int tr, int k) {
    if (tl == tr) return tl;
    int tm = (tl + tr) >> 1;
    if (t[v << 1] < k) return find(v << 1, tl, tm, k);
    return find(v << 1 | 1, tm + 1, tr, k);
}

void solve(int case_no) {

    memset(t, 0, sizeof t);
    memset(last, 0, sizeof last);
    memset(works, 0, sizeof works);

    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    int x;

    for (int i = 1; i <= n; ++i) {
        cin >> x;
        if (last[x] + 1 < i) works[find(1, 1, M, last[x] + 1)] = 1;
        update(1, 1, M, x, i);
        last[x] = i;
    }

    works[find(1, 1, M, 1)] = 1;
    
    for (int i = 1; i < N; ++i) {
        if (last[i] != 0 && last[i] != n) {
            works[find(1, 1, M, last[i] + 1)] = 1;
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (!works[i]) {
            cout << i << '\n';
            return;
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

