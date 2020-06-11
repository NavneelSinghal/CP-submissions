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

//const int mod = 1e9 + 7;
const int mod = 998244353;

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
    vi a(n);
    rep(i, n) cin >> a[i];
    vi b(m);
    rep(i, m) cin >> b[i];
    vi postmin(n);
    int mn = INF;
    repd(i, n){
        mn = min(mn, a[i]);
        postmin[i] = mn;
    }
    bool works = true;
    vi idx(m);
    for(int i = 0; i < m; i++){
        int left = 0;
        int right = n-1;
        int ans = 0;
        while(left <= right){
            int mid = (left + right)/2;
            if(postmin[mid] <= b[i]){
                ans = mid;
                left = mid + 1;
            }
            else right = mid - 1;
        }
        if(postmin[ans] == b[i]){
            idx[i] = ans;
        }
        else{
            works = false;
            cout << 0 << endl;
            return;
        }
    }
    if(b[0] != postmin[0]){
        cout << 0 << endl;
        return;
    }
    int ans = 1;
    for(int i = 1; i < m; i++){
        int k = idx[i];
        while(k >= 0 && postmin[k] == postmin[idx[i]]){
            k--;
        }
        ans = (ans * (idx[i] - k)) % mod;
    }
    cout << ans << endl;
    
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
