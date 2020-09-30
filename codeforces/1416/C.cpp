#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 3e5 + 5;

int a[N], f[N], temp[N];

int inv (int l, int r) {
    
    if (l >= r) return 0;
    
    int m = (l + r) >> 1;
    
    int ans = 0;

    ans += inv(l, m);
    ans += inv(m + 1, r);
    
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (f[i] <= f[j]) {
            temp[k] = f[i];
            ++i, ++k;
        } else {
            temp[k] = f[j];
            ++k, ++j;
            ans += m - i + 1;
        }
    }
    
    while (i <= m) {
        temp[k] = f[i];
        ++i, ++k;
    }
    
    while (j <= r) {
        temp[k] = f[j];
        ++j, ++k;
    }
    
    for (int i = l; i <= r; ++i) f[i] = temp[i];
    return ans;
}

void solve() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        f[i] = a[i];
    }

    int ans = inv(0, n - 1);
    int x = 0;
    
    for (int bit = 31; ~bit; --bit) {
        
        x ^= (1LL << bit);
        
        for (int i = 0; i < n; ++i) f[i] = a[i] ^ x;
        
        int t = inv(0, n - 1);
        
        if (t < ans) ans = t;
        else x ^= (1LL << bit);
    
    }
    
    cout << ans << ' ' << x << '\n';
    return;
}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
