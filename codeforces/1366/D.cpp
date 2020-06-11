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

//#define int long long
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

const int maxn = 1e7+7;

vi prod(maxn, 1);
vi smallest(maxn, INF);
vi num(maxn);

void precompute(){
    for(int i = 2; i < maxn; i++){
        if(num[i] == 0){
            smallest[i] = i;
            for(int j = i; j < maxn; j+=i){
                if(smallest[j] == INF){
                    smallest[j] = i;
                }
                prod[j] *= i;
                num[j]++;
            }
        }
    }
}

void solve(){
    precompute();
    int n;
    cin >> n;
    vi a, b;
    rep(i, n) {
        int x;
        cin >> x;
        if(num[x] < 2){
            a.pb(-1);
            b.pb(-1);
        }
        else{
            a.pb(prod[x]/smallest[x]);
            b.pb(smallest[x]);
        }
    }
    for(auto x : a) cout << x << " ";
    cout << endl;
    for(auto x : b) cout << x << " ";
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
