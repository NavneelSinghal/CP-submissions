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

int diff(string &a, string &b){
    int n = a.size();
    int ans = 0;
    rep(i, n){
        if(a[i] != b[i]) ans++;
    }
    return ans;
}

signed main() {
    
    fastio;
    int t; cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> v(n);
        rep(i, n) cin >> v[i];
        string ans = "-1";
        rep(i, m){
            //replace ith with *
            string s = v[0];
            s[i] = '*';
            int nstar = 1;
            bool feasible = true;
            for(int ii = 0; ii < n; ii++){
                int d = diff(v[ii], s);
                if(d <= 1) continue;
                if(d == 2 && nstar == 1){
                    nstar--;
                    s[i] = v[ii][i];
                }
                else{
                    feasible = false;
                    break;
                }
            }
            if(feasible){
                if(nstar == 0){
                    ans = s;
                }
                else{
                    ans = v[0];
                }
                break;
            }
        }
        cout << ans << "\n";
    }

}
