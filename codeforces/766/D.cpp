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

string u, v;
int n, m, q;
int t;
string s[100100];
map <string, int> id;
int p[200200];
 
int get(int v){
    if(p[v] == v) return v;
    return p[v] = get(p[v]);
}
 
void solve(){
    cin >> n >> m >> q;
    for(int i = 0; i < n; ++i){
        cin >> s[i];
        id[s[i]] = i;
        p[i] = i;
        p[i + n] = i + n;
    }
    for(int i = 0; i < m; ++i){
        cin >> t >> u >> v;
        int x = id[u];
        int y = id[v];
        if(t == 1){
            if(get(x) == get(y + n)) cout << "NO" << "\n";
            else{
                if(get(x) != get(y)){
                    p[get(x)] = get(y);
                }
                if(get(x + n) != get(y + n)){
                    p[get(x + n)] = get(y + n);
                }
                cout << "YES" << "\n";
            }
        }
        else{
            if(get(x) == get(y)) cout << "NO" << "\n";
            else{
                if(get(x) != get(y + n)){
                    p[get(x)] = get(y + n);
                }
                if(get(x + n) != get(y)){
                    p[get(x + n)] = get(y);
                }
                cout << "YES" << "\n";
            }
        }
    }
    for(int i = 0; i < q; ++i){
        cin >> u >> v;
        int x = id[u];
        int y = id[v];
        if(get(x) == get(y)) cout << 1 << "\n";
        else{
            if(get(x) == get(y + n)) cout << 2 << "\n";
            else cout << 3 << "\n";
        }
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
