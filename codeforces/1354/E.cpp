#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pair<int, int>> 
#define mii map<int, int>
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
#define LIM 2e6

vi visited(5005), col(5005), compo(0);
vvi g(5005);
int count_tot = 0, count_tot1 = 0;

void dfs(int v, int c){
    visited[v] = true;
    count_tot++;
    col[v] = c;
    compo.pb(v);
    if(c == 1) count_tot1++;
    for(auto x : g[v]){
        if(!visited[x]){
            dfs(x, 3-c);
        }
    }
}

void solve(){
    int n, m;
    cin >> n >> m;
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    rep(i, m){
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[v].pb(u);
        g[u].pb(v);
    }
    vpii sizes;
    vvi comps;
    rep(i, n){
        if(!visited[i]){
            count_tot = 0;
            count_tot1 = 0;
            compo = vi();
            dfs(i, 1);
            sizes.eb(count_tot1, count_tot - count_tot1);
            comps.pb(compo);
        }
    }
    rep(i, n){
        for(auto x : g[i]){
            if(col[x] == col[i]){
                cout << "NO\n";
                return;
            }
        }
    }
    vector<vector<bool>> dp(sizes.size() + 1, vector<bool>(n+1, false));
    vector<vector<int>> siz(sizes.size() + 1, vector<int>(n+1, 0));
    dp[0][0] = true;
    for(int i = 1; i <= sizes.size(); i++){
        for(int j = 0; j < n; j++){
            if(dp[i - 1][j]){
                dp[i][j + sizes[i - 1].first] = true;
                dp[i][j + sizes[i - 1].second] = true;
                siz[i][j + sizes[i - 1].first] = sizes[i - 1].first;
                siz[i][j + sizes[i - 1].second] = sizes[i - 1].second;
            }
        }
    }
    if(!dp[sizes.size()][n2]){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int ctr = 0;
    int curn = n2;
    for(int i = sizes.size(); i >= 1; i--){
        if(siz[i][curn] == sizes[i - 1].first){
            //for each vertex in component, replace 1s by 2s and 2s by 1s if ctr < n1 else n3
            for(auto x : comps[i - 1]){
                if(col[x] == 1){
                    col[x] = 2;
                }
                else{
                    if(ctr < n1){
                        col[x] = 1;
                        ctr++;
                    }
                    else{
                        col[x] = 3;
                    }
                }
            }
        }
        else{
            for(auto x : comps[i - 1]){
                if(col[x] == 1){
                    if(ctr >= n1){
                        col[x] = 3;
                    }
                    else{
                        ctr++;
                    }
                }
            }
        }
        curn -= siz[i][curn];
    }
    rep(i, n) cout << col[i];
    cout << "\n";
}

signed main(){
    fastio;
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
} 
