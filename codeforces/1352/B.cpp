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


void solve(){
    int n, k;
    cin >> n >> k;
    if(n < k || (n % 2 == 1 && k % 2 == 0)){
        cout << "NO\n";
    }
    else{
        if(n % 2 == 0){
            if(k % 2 == 1){
                if(n < 2*k) cout << "NO\n";
                else{
                    cout << "YES\n";
                    for(int i = 0; i < k - 1; i++){
                        cout << 2 << " ";
                    }
                    cout << n - 2 * k + 2 << "\n";
                }
            }
            else{
                cout << "YES\n";
                for(int i = 0; i < k - 1; i++){
                    cout << 1 << " ";
                }
                cout << n - k + 1 << "\n";
            }
        }
        else{
            //k % 2 == 1
            cout << "YES\n";
            for(int i = 0; i < k - 1; i++){
                cout << 1 << " ";
            }
            cout << n - k + 1 << "\n";
        }
    }
}

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        solve();
    }
} 
