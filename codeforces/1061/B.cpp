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
    int n, m;
    cin >> n >> m;
    vi a(n);
    int sum = 0;
    rep(i, n){
        cin >> a[i];
        sum += a[i];
    }
    a.push_back(0);
    sort(all(a));
    int s = 0; 
    for(int i = 1; i <= n; i++) s += a[i];
    int h = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans++;
        if(h < a[i]) h++;
    }
    for(; h <= a[n] - 1; h++) {
        ans++;
    }
    cout << s - ans << endl;
} 

