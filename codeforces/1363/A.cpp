#include <bits/stdc++.h>
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

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        int odd = 0;
        int even = 0;
        rep(i, n){
            int w;
            cin >> w;
            if(w % 2 == 0) even++;
            else odd++;
        }
        if(x <= even){
            if(odd >= 1){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
        else{
            x -= even;
            //now x can only take odd values
            if(x < odd && even >= 1){
                cout << "YES\n";
            }
            else if(x == odd){
                if(x % 2 == 1){
                    cout << "YES\n";
                }
                else{
                    cout << "NO\n";
                }
            }
            else{
                if(x % 2 == 0){
                    cout << "NO\n";
                }
                else{
                    cout << "YES\n";
                }
            }
        }
    }
} 
