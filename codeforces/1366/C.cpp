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


void solve(){
    int n, m;
    cin >> n >> m;
    vvi a(n, vi(m));
    rep(i, n) rep(j, m) cin >> a[i][j];
    vvi b(n, vi(m));
    rep(i, n) rep(j, m) b[i][j] = a[n-i-1][m-j-1];
    if(n < m){
        vvi c(m, vi(n));
        rep(i, n) rep(j, m) c[j][i] = b[i][j];
        vvi d(m, vi(n));
        rep(i, n) rep(j, m) d[j][i] = a[i][j];
        b = c;
        a = d;
        swap(m, n);
    }
    int ans = 0;
    for(int i = 0; i < (m + n - 1)/2; i++){
        int cnta1 = 0;
        int cntb1 = 0;
        int cnta0 = 0;
        int cntb0 = 0;
        for(int j = 0; j < min(i+1, m); j++){
            int w = a[i-j][j];
            int x = b[i-j][j];
            if(w == 0) cnta0++;
            else cnta1++;
            if(x == 0) cntb0++;
            else cntb1++;
        }
        int tot1 = cnta1+cntb1;
        int tot0 = cnta0+cntb0;
        ans += min(tot1, tot0);
    }
    cout << ans << endl;
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
