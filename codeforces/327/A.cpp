#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for(auto &x : a) cin >> x, sum += x;
    vector<int> change(n+1);
    int c = 0;
    for(int i = 0; i <= n; i++){
        change[i] = c;
        if(i < n) c += 1 - 2*a[i];
    }
    int mn = 0;
    int ans = -INF;
    for(int i = 1; i <= n; i++){
        ans = max(ans, change[i] - mn);
        mn = min(mn, change[i]);
    }
    cout << ans + sum << endl;
}
