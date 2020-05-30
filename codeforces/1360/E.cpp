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
        vector<string> a(n);
        vi rangeh(n), rangev(n);
        for(auto &x : rangeh) x = n - 1;
        for(auto &x : rangev) x = n - 1;
        bool feasible = true;
        for(auto &x : a) {
            cin >> x;
            x += "1";
        }
        string s;
        for(int i = 0; i < n + 1; i++){
            s += "1";
        }
        a.pb(s);
        for(int _i = n-1; _i >= 0; _i--){
            int last = _i;
            for(int i = _i; i >= 0; i--){
                int j = last;
                if(a[i][j] == '1'){
                    if(a[i][j+1] == '0' && a[i+1][j] == '0'){
                        feasible = false;
                        break;
                    }
                }
            }
            for(int j = _i; j >= 0; j--){
                int i = last;
                if(a[i][j] == '1'){
                     if(a[i][j+1] == '0' && a[i+1][j] == '0'){
                         feasible = false;
                         break;
                     }
                 }
            }
        }
        if(!feasible) cout << "NO\n";
        else cout << "YES\n";
    }

}
