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


signed main() {
    fastio;
    int q;
    cin >> q;
    while(q--){
        int b, w;
        cin >> b >> w;
        if(b > 3 * w + 1 || w > 3 * b + 1) cout << "NO\n";
        else{
            int x = min(b, w);
            int y = max(b, w);
            vpii ans;
            rep(i, 2*x){
                ans.eb(3, i+1);
            }
            int rem = y - x;
            if(rem <= x){
                for(int i = 0; i < rem; i++){
                    ans.eb(2, 2*i + 2);
                }
            }
            else if(rem <= 2*x){
                for(int i = 0; i < x; i++){
                    ans.eb(2, 2*i + 2);
                }
                for(int i = 0; i < rem - x; i++){
                    ans.eb(4, 2*i + 2);
                }
            }
            else{
                for(int i = 0; i < x; i++){
                    ans.eb(2, 2*i + 2);
                    ans.eb(4, 2*i + 2);
                }
                ans.eb(3, 2*x + 1);
            }
            for(auto &p : ans){
                if(b > w) p.F++;
            }
            int cntw = 0, cntb = 0;
            for(auto &p : ans){
                if((p.F + p.S) % 2 == 0) cntw ++;
                else cntb ++;
            }
            assert(cntw == w && cntb == b);
            cout << "YES\n";
            for(auto p : ans){
                cout << p.F << " " << p.S << "\n";
            }
        }
    }
}

