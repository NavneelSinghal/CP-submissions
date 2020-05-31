#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pair<int, int>> 
#define rep(i, n) for(int i = 0; i < n; i++)
#define repd(i, n) for(int i = n-1; i >= 0; i--)
#define F first
#define S second
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()
#define INF 1e9

const int mod = 1e9+7;

signed main(){

    fastio;
    int n, m;
    cin >> n;
    vi a(n+1000), dp(1000006);
    int ans = 0;
    dp[0] = 1;
    rep(i, n){
        cin >> a[i];
        vector<int> v;
        for(int j = 1; j*j <= a[i]; j++){
            if(a[i] % j == 0){
                v.pb(j);
                if(j != a[i]/j) v.pb(a[i]/j);
            }
        }
        sort(all(v));
        reverse(all(v));
        for(auto x : v){
            dp[x] += dp[x-1];
            dp[x] %= mod;
        }
    }
    for(auto x : dp){
        ans += x;
        ans %= mod;
    }
    cout << ans-1 << endl;
} 

