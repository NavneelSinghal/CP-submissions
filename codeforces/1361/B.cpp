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

const int mod = 1e9 + 7;

int powerp(int a, int e){
    int ans = 1;
    while(e){
        if(e & 1){
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        e >>= 1;
    }
    return ans;
}

void solve(){
    int n, p;
    cin >> n >> p;
    if(p == 1){
        rep(i, n){
            int x;
            cin >> x;
        }
        cout << n%2 << "\n";
        return;
    }
    vi a(n);
    rep(i, n) cin >> a[i];

    int prev = 1e6 + 20;
    
    sort(all(a));
    vi working = a;
    
    int cur = 0;
    int res = 0;
    int toobig = false;
    
    while(!a.empty()){
        int k = a.back();
        int change = prev - k;
        a.pop_back();
        prev = k;
        res = (res * powerp(p, change)) % mod;
        rep(i, min(change, 20ll)){
            cur *= p;
            if(cur > INF) toobig = true;
        }
        while(!working.empty() && working.back() == k){
            working.pop_back();
            if(toobig || cur > 0){
                --cur;
                res = (res + mod - 1) % mod;
            }
            else{
                ++cur;
                res = (res + 1) % mod;
            }
        }
    }
    res = (res * powerp(p, prev)) % mod;
    cout << res << "\n";
}

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        solve();
    }
} 
