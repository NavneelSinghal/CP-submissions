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
        int n;
        cin >> n;
        vi a(n);
        rep(i, n) cin >> a[i];
        vvi par(2);
        rep(i, n){
            par[a[i] % 2].pb(a[i]);
        }
        if(par[0].size() % 2 == 0){
            cout << "YES\n";
        }
        else{
            bool found = false;
            sort(all(a));
            rep(i, n-1){
                if(a[i+1] - a[i] == 1){
                    cout << "YES\n";
                    found = true;
                    break;
                }
            }
            if(!found) cout << "NO\n";
        }
    }

}
