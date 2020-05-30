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

int intbin(string s){
    int p = 1;
    int ans = 0;
    for(int i = s.size() - 1; i >= 0; i--){
        if(s[i] == '1') ans += p;
        p += p;
    }
    return ans;
}

string binint(int a, int m){
    string ans;
    rep(i, m) ans += '0';
    for(int i = m-1; i >= 0; i--){
        ans[i] = '0' + (a & 1);
        a /= 2;
    }
    return ans;
}

signed main() {
    
    fastio;
    int t; cin >> t;
    while(t--){
        int n;
        cin >> n;
        int m;
        cin >> m;
        vi a;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            a.pb(intbin(s));
        }
        a.pb((1LL << m));
        sort(all(a));
        int tot = (1LL << m) - n; //total number of numbers
        int num = 0;
        int mednum = (tot+1)/2;
        for(int i = 0; i <= n; i++){
            num = a[i] - i;
            if(num >= mednum){
                cout << binint(a[i] - 1 - (num - mednum), m) << "\n";
                break;
            }
        }
    }

}
