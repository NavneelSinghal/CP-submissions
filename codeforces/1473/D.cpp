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
    
    int n, q;
    cin >> n >> q;
    
    string s;
    cin >> s;
    
    vector<int> pre(n + 1), maxpre(n + 1), minpre(n + 1), sufmax(n + 1), sufmin(n + 1);
    vector<int> a(n);
    
    for (int i = 0; i < n; ++i) {
        a[i] = (s[i] == '+') ? 1 : -1;
    }
    
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i - 1];
        maxpre[i] = max(maxpre[i - 1], pre[i]);
        minpre[i] = min(minpre[i - 1], pre[i]);
    }

    // sufmin[i] = min(pre[i+1]...pre[n])
    // sufmax[i] = max(pre[i+1]...pre[n])
    sufmin[n - 1] = pre[n];
    sufmax[n - 1] = pre[n];
    for (int i = n - 2; i >= 0; --i) {
        sufmin[i] = min(sufmin[i + 1], pre[i + 1]);
        sufmax[i] = max(sufmax[i + 1], pre[i + 1]);
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        int x1, y1;
        int x2, y2;
        x1 = minpre[l - 1];
        y1 = maxpre[l - 1];
        if (r == n) {
            x2 = x1;
            y2 = y1;
        } else {
            x2 = pre[l - 1] - pre[r] + sufmin[r];
            y2 = pre[l - 1] - pre[r] + sufmax[r];
        }
        // cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
        cout << merge_ranges(x1, y1, x2, y2) << '\n';
    }
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
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
