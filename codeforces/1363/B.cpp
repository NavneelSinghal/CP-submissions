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
        string a;
        cin >> a;
        //case 1 - 0000...00 - 11100000 - 111111111111
        int ans = 0;
        int n = a.size();
        for(int i = 0; i < n; i++){
            ans += a[i] - '0';
        }
        //for all zeros
        int cur = ans;
        int best = ans;
        rep(i, n){
            if(a[i] == '1') ans = ans - 1;
            else ans = ans + 1;
            best = min(best, ans);
        }
        //now case 2 00000 - 00000001 - 1111111
        repd(i, n){
            if(a[i] == '1') cur = cur - 1;
            else cur = cur + 1;
            best = min(best, cur);
        }
        ans = min(ans, cur);
        cout << best << endl;
    }
} 
