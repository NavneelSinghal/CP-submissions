#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    int t = (n + 1)/2;
    vector<int> a(t);
    int s = 0;
    for(int i = 0; i < t; i++){
        cin >> a[i];
        s += a[i];
    }
    int x;
    cin >> x;
    int p = 0;
    vector<int> pre(t+1);
    for(int i = 0; i < t; i++){
        p += x - a[i];
        pre[i+1] = min(pre[i], p);
    }
    for(int i = t; i <= n; i++){
        if(s + pre[n-i] > 0){
            cout << i << endl;
            return 0;
        }
        s += x;
    }
    cout << -1 << endl;
    return 0;
}
