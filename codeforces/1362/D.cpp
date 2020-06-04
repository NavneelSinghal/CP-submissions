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

void solve(){
    int n, m;
    cin >> n >> m;
    int a, b;
    vvi g(n);
    rep(i, m){
        cin >> a >> b;
        --a, --b;
        g[a].pb(b);
        g[b].pb(a);
    }
    vpii t(n);
    rep(i, n) cin >> t[i].first;
    rep(i, n) t[i].second = i;
    sort(all(t));
    vi blog(n, 1);
    rep(i, n){
        if(blog[t[i].second] == t[i].first){
            for(auto x : g[t[i].second]){
                if(blog[x] == t[i].first){
                    blog[x]++;
                }
            }
        }
        else{
            cout << -1 << "\n";
            return;
        }
    }
    rep(i, n){
        cout << t[i].second + 1 << " ";
    }
    cout << "\n";
    return;
}

signed main(){
    fastio;
    int t;
    t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
} 
