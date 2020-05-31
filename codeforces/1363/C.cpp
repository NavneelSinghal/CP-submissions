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

#if 0
void dfs(int v, int p, vi &sz, vi &g){
    int s = 0;
    for(auto u : g[v]){
        if(u != p){
            dfs(u, v, sz, g);
            s += sz[u];
        }
    }
    sz[v] = s + 1;
}
#endif

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int x;
        cin >> x;
        vvi g(n);
        rep(i, n-1){
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].pb(v);
            g[v].pb(u);
        }
        vi sz(n);
        //dfs(x, -1, sz, g);
        if(g[--x].size() > 1){
            if(n % 2 == 0){
                cout << "Ayush\n";
            }
            else{
                cout << "Ashish\n";
            }
        }
        else{
            cout << "Ayush\n";
        }
        
    }
} 
