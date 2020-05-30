#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define rep(i, n) for(int i = 0; i < n; i++)
#define repd(i, n) for(int i = n-1; i >= 0; i--)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

#define INF 1e9

void shift(string &a){
    string b;
    b += a.back();
    b += a;
    b.pop_back();
    a = b;
}

signed main() {
    
    fastio;
    int t; cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int a, b;
        cin >> a >> b;
        if(n * a != m * b || a > m){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        int g = __gcd(a, m);
        int a1 = a/g;
        int m1 = m/g;
        string unit = "";
        for(int i = 0; i < m1; i++){
            if(i < a1) 
                unit += '1';
            else
                unit += '0';
        }
        string ans = "";
        for(int i = 0; i < g; i++){
            ans += unit;
        }
        for(int i = 0; i < n; i++){
            cout << ans << "\n";
            shift(ans);
        }
    }

}
