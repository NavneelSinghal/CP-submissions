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

int w;

int query(int x){
    cout << "? " << x;
    rep(i, x) cout << " " << i + 1;
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void solve(){
    int n, k;
    cin >> n >> k;
    vvi v(k);
    rep(i, k){
        int s;
        cin >> s;
        v[i].resize(s);
        rep(j, s) cin >> v[i][j];
    }
    int mx = query(n);
    int left = 1;
    int right = n;
    int ans = 0;
    while(left <= right){
        int mid = (left + right)/2;
        int res = query(mid);
        if(res == mx){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    vi fin(k);
    for(int i = 0; i < k; i++){
        bool flag = false;
        for(auto x : v[i]) flag = flag || (x == ans);
        if(!flag){
            fin[i] = mx;
        }
        else{
            vector<bool> present(n);
            for(auto x : v[i]) present[x-1] = 1;
            cout << "? " << n - v[i].size() << " ";
            rep(i, n) if(!present[i]) cout << i+1 << " ";
            cout << endl;
            cin >> fin[i];
        }
    }
    cout << "! ";
    for(auto x : fin) cout << x << " ";
    cout << endl;
    string result;
    cin >> result;
    assert(result == "Correct");
}

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        solve();
    }
} 
