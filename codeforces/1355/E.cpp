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

int n, A, R, M;
vi a;
vi pre;

int work(int h){
    int i = lower_bound(all(a), h) - a.begin();
    int surplus = pre[n] - pre[i] - (n - i) * h;
    int deficit = i * h - pre[i] ;
    if(surplus >= deficit){
        return deficit * M + (surplus - deficit) * R;
    }
    else{
        return surplus * M + (deficit - surplus) * A;
    }
}

signed main() {
    fastio;
    cin >> n >> A >> R >> M;
    M = min(M, A + R);

    a.resize(n);
    pre.resize(n+1);

    rep(i, n) cin >> a[i];
    sort(all(a));
    
    int h = 0, p = 0;
    rep(i, n) h += a[i];
    h /= n;
    rep(i, n){
        p += a[i];
        pre[i+1] = p;
    }
    int ans = min(work(h), work(h+1));
    rep(i, n){
        ans = min(ans, work(a[i]));
    }
    cout << ans << endl;
}
