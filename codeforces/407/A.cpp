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

inline long long isqrt(long long n){
    long double N = n;
    N = sqrtl(N);
    long long sq = N-2;
    sq = max(sq,0LL);
    while(sq*sq<n){
        sq++;
    } 
    if((sq*sq)==n)
        return sq;
    return -1;
}

bool checksq(int n){
    int cand = isqrt(n);
    return cand * cand == n;
}

vpii work(int a){
    vpii ans;
    for(int i = 1; i < a; i++){
        if(checksq(a*a - i*i)){
            ans.eb(i, isqrt(a*a - i*i));
        }
    }
    return ans;
}

void solve(){
    int a, b;
    cin >> a >> b;
    vpii p1 = work(__gcd(a, b));
    if(p1.size() == 0){
        cout << "NO\n";
        return;
    }
    else{
        int g = __gcd(a, b);
        int wb = b / g;
        int wa = a / g;
        for(auto p : p1){
            if(wa * p.F != wb * p.S){
                cout << "YES\n0 0\n";
                cout << wa * p.F << " " << wa * p.S << "\n";
                cout << wb * p.S << " " << -wb * p.F << "\n";
                return;
            }
        }
        cout << "NO\n";
        return;
    }
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
