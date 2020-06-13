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
#define double long double
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define vpii vector<pii> 
#define vvpii vector<vpii>
#define mii map<int, int>
#define rep(i, n) for(int i = 0; i < n; i++)
#define rep2(i, a, b) for(int i = a; i < b; i++)
#define repd2(i, a, b) for(int i = b - 1; i >= a; i--)
#define repd(i, n) for(int i = n-1; i >= 0; i--)
#define F first
#define S second
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()
#define INF 2e9
#define EPS 1e-9
#define PI acosl(-1)

const int mod = 1e9 + 7;
const int maxn = 1e5 + 5;

int powmod (int a, int n) {
    int ans = 1;
    while(n) {
        if(n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

int inv (int a) {
    return powmod(a, mod-2);
}

int n, m, k;
vi g[maxn];
int h[maxn], par[maxn];
vi vec[2];

void print(int start, int end){
    vi cycle;
    while(start != end){
        cycle.pb(start);
        start = par[start];
    }
    cycle.pb(end);
    cout << 2 << endl << cycle.size() << endl;
    for(auto x : cycle){
        cout << x + 1 << " ";
    }
    cout << endl;
}

void dfs(int u){
    for(auto v : g[u]){
        if(v == par[u]) continue;
        if(h[v] != 0 && h[v] < h[u]){
            print(u, v);
            exit(0);
        }
        par[v] = u;
        h[v] = h[u] + 1;
        dfs(v);
    }
}

void solve(){
    cin >> n >> m >> k;
    rep(i, m){
        int u, v;
        cin >> u >> v;
        if(u > k || v > k) continue;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
        rep(i, k){
            if(h[i]) continue;
            h[i] = 1;
            dfs(i);
        }
        rep(i, k){
            vec[h[i] % 2].pb(i);
        }
        if(vec[0].size() < vec[1].size()) swap(vec[0], vec[1]);
        cout << 1 << "\n";
        rep(i, (k+1)/2){
            cout << 1 + vec[0][i] << " ";
        }
        cout << endl;
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
