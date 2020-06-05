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
#define vvi vector<vi>
#define pii pair<int, int>
#define vpii vector<pii> 
#define vvpii vector<vpii>
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
#define EPS 1e-9
#define PI acosl(-1)

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vvpii g(n);
    rep(i, m){
        int u, v, l; cin >> u >> v >> l;
        g[--u].eb(--v, l);
        g[v].eb(u, l);
    }
    vector<bool> storage(n, false);
    rep(i, k){
        int x;
        cin >> x;
        --x;
        storage[x] = true;
    }
    int ans = INF * 2;
    rep(i, n){
        if(storage[i]){
            for(auto w : g[i]){
                if(!storage[w.first]){
                    ans = min(ans, w.second);
                }
            }
        }
    }
    if(ans == INF * 2) cout << -1 << endl;
    else cout << ans << endl;
}

signed main(){
    fastio;
    cout << setprecision(20) << fixed;
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
} 
