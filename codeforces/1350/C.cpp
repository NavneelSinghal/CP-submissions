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

const int maxn = 2e5 + 5;

signed main(){
    fastio;
    int n;
    cin >> n;
    vi a(n);
    rep(i, n) cin >> a[i];
    vi pre(n), post(n), g(n);
    for(int i = 0; i < n-1; i++) pre[i+1] = __gcd(pre[i], a[i]);
    for(int i = n-1; i > 0; i--) post[i-1] = __gcd(post[i], a[i]);
    for(int i = 0; i < n; i++) g[i] = __gcd(pre[i], post[i]);
    int g0 = 0;
    for(int i = 0; i < n; i++){
        g0 = __gcd(g0, a[i]);
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = __gcd(ans, a[i] * g[i]);
    }
    ans /= g0;
    cout << ans << endl;
    return 0;
} 
