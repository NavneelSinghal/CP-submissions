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

const int maxn = 1e6;

int work(int x){
    int left = 0;
    int right = x;
    int ans = 0;
    while(left <= right){
        int mid = (left + right)/2;
        if(mid * (mid + 1) / 2 <= x){
            ans = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return ans;
}

void solve(){
    int n;
    cin >> n;
    vi powers;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            int cnt = 0;
            while(n % i == 0){
                cnt ++;
                n /= i;
            }
            powers.pb(cnt);
        }
    }
    if(n > 1){
        powers.pb(1);
    }
    int ans = 0;
    for(auto x : powers){
        ans += work(x);
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
