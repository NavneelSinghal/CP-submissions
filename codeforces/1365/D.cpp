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
#define INF 1e9
#define EPS 1e-9
#define PI acosl(-1)

const int mod = 1e9 + 7;

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


int n, m;

bool check(int i, int j){
    return 0 <= i && i < n && 0 <= j && j < m;
}

vpii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int i, int j, vector<string> &a, vvi &visited) {
    if(a[i][j] != '#') {
        visited[i][j] = true;
        for(auto p : dir) {
            int i1 = i + p.first;
            int j1 = j + p.second;
            if(check(i1, j1) && !visited[i1][j1]) {
                dfs(i1, j1, a, visited);
            }
        }
    }
}

void solve(){
    cin >> n >> m;
    vector<string> a(n);
    vvi visited(n, vi(m));
    rep(i, n) cin >> a[i];
    int initcountg = 0;
    rep(i, n) rep(j, m) if(a[i][j] == 'G') initcountg++;
    rep(i, n){
        rep(j, m){
            if(a[i][j] == 'B'){
                for(auto p : dir){
                    if(check(p.first + i, p.second + j)){
                        int i1 = i + p.first;
                        int j1 = j + p.second;
                        if(a[i1][j1] != 'G' && a[i1][j1] != 'B') {
                            a[i1][j1] = '#';
                        }
                    }
                }
            }
        }
    }
    int countg = 0;
    int countb = 0;
    dfs(n-1, m-1, a, visited);
    rep(i, n) rep(j, m){
        if(visited[i][j]) {
            if(a[i][j] == 'G'){
                countg++;
            }
            else if(a[i][j] == 'B') {
                countb++;
            }
        }
    }
    if(countg == initcountg && countb == 0){
        cout << "Yes\n";
    }
    else cout << "No\n";
}

signed main(){
    fastio;
    cout << setprecision(20) << fixed;
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
} 
