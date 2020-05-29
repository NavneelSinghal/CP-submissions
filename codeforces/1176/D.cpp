#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    
    const int maxn = 3e6;

    vector<int> prime(maxn);
    vector<int> spd(maxn);
    int idx = 1;
    prime[0] = -1;
    prime[1] = -1;
    for(int i = 0; i < 3000000; i++){
        if(prime[i] != -1){
            prime[i] = idx;
            idx++;
            for(int j = i*i; j < maxn; j += i){
                prime[j] = -1;
                if(spd[j] == 0) spd[j] = i;
            }
        }
    }
    multiset<int> m;
    for(int i = 0; i < 2 * n; i++){
        int x;
        cin >> x;
        m.insert(x);
    }
    for(int i = 0; i < n; i++){
        int mx = *m.rbegin();
        int ans;
        if(prime[mx] != -1){
            ans = prime[mx];
            cout << ans << " ";
        }
        else{
            ans = mx/spd[mx];
            cout << mx << " ";
        }
        m.erase(m.lower_bound(mx));
        m.erase(m.lower_bound(ans));
    }
    cout << endl;
}

