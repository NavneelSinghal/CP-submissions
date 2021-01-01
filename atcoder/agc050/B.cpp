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

// const int mod = 998244353;
const int mod = 1e9 + 7;

long long pwr(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}



template<typename X, typename Y> 
X& remin(X& x, const Y& y) { return x = (y < x) ? y : x; }

template<typename X, typename Y>
X& remax(X& x, const Y& y) { return x = (x < y) ? y : x; }

template<typename X, typename Y>
bool ckmin(X& x, const Y& y) { return (y < x) ? (x = y, 1) : 0; }

template<typename X, typename Y>
bool ckmax(X& x, const Y& y) { return (x < y) ? (x = y, 1) : 0; }

void precompute() {
}

void solve(int _) {
    
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -mod));
    
    for (int i = 0; i <= n; ++i) {
        dp[0][i] = 0;
    }

    for (int i = 3; i <= n; i += 3) {
        for (int j = 0; i + j <= n; ++j) {
            for (int k = 0; k < i; k += 3) {
                remax(dp[i][j], dp[k][j] + dp[i - k][j + k]);
                remax(dp[i][j], dp[k][j + 1] + dp[i - k - 3][j + k + 2] + max(0, a[j] + a[i + j - 1] + a[j + k + 1]));
            }
            remax(dp[i][j], dp[i - 3][j] + max(0, a[i + j - 1] + a[i + j - 2] + a[i + j - 3]));
			remax(dp[i][j], dp[i - 3][j + 3] + max(0, a[j] + a[j + 1] + a[j + 2]));
        }
    }
    vector<int> ans(n + 1, -mod);
	ans[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; i + j <= n; j += 3) {
			remax(ans[i + j], ans[i] + dp[j][i]);
		}
		remax(ans[i + 1], ans[i]);
	}
	cout << ans.back() << endl;
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
