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

void solve(int case_no) {
    
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 2), b(k + 2);
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i + 1];
        a[i + 1] -= i + 1;
    }
    
    a[0] = -1e9;
    a[n + 1] = 1e9;
    
    int ans = 0;
    int l = 0, r = 0;
    
    for (int i = 0; i <= k; ++i) {
    
        if (i == k) r = n + 1;
        else cin >> r;

        if (a[l] > a[r]) {
            cout << -1 << '\n';
            return;
        }

        vector<int> lis;
        
        for (int j = l + 1; j < r; ++j) {
            if (a[l] <= a[j] && a[j] <= a[r]) {
                auto ptr = upper_bound(lis.begin(), lis.end(), a[j]);
                if (ptr == lis.end()) lis.push_back(a[j]);
                else *ptr = a[j];
            }
        }
        
        ans += (r - l - 1) - (int) lis.size();
        l = r;
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

