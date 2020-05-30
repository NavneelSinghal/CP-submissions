#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    int mn = *min_element(a.begin(), a.end());
    int idx = n;
    for(int i = n-1; i >= 0; i--){
        if(a[i] == mn){
            while(i >= 0 && a[i] == mn){
                idx = i;
                i--;
            }
            break;
        }
    }
    bool fail = false;
    int ans = (n - idx) % n;
    for(int i = 0; i < n-1; i++){
        if(a[idx] > a[(idx + 1) % n]){
            fail = true;
            break;
        }
        idx = (idx + 1) % n;
    }
    if(!fail) cout << ans << endl;
    else cout << -1 << endl;
}
