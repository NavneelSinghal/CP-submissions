#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define rep(i, n) for(int i = 0; i < n; i++)
#define repd(i, n) for(int i = n-1; i >= 0; i--)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

#define INF 1e9

signed main() {
    
    fastio;
    int t; cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        //check if n is prime
        vi div;
        for(int i = 1; i*i <= n; i++){
            if(n % i == 0){
                div.pb(i);
                div.pb(n/i);
            }
        }
        sort(all(div));
        int mx = 1;
        for(auto x : div){
            if(x <= k) mx = x;
        }
        cout << n/mx << "\n";
    }

}
