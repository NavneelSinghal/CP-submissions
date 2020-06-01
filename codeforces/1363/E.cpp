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

const int maxn = 2e5 + 5;

int n;
vi val(maxn), init(maxn), tar(maxn);
vvi g(maxn);
int ans = 0;

pii dfs(int v, int p, int curcost){
    pii ret = {0, 0};
    if(init[v] != tar[v]){
        ret.F = init[v];
        ret.S = tar[v];
    }
    for(auto u : g[v]){
        if(u != p){
            pii x = dfs(u, v, min(curcost, val[v]));
            ret.F += x.F;
            ret.S += x.S;
        }
    }
    if(val[v] < curcost){
        int work = min(ret.F, ret.S);
        ret.F -= work;
        ret.S -= work;
        ans += 2 * work * val[v];
    }
    return ret;
}

signed main(){
    fastio;
    cin >> n;
    rep(i, n){
        cin >> val[i+1] >> init[i+1] >> tar[i+1];
    }
    rep(i, n-1){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    pii ret = dfs(1, 0, 2*INF);
    if(ret.F != ret.S){
        cout << -1 << endl;
    }
    else{
        cout << ans << endl;
    }

} 
