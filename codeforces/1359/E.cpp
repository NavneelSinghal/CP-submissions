#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

#define MOD 998244353

int powm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1){
            ans *= a;
            ans %= MOD;
        }
        a = (a*a) % MOD;
        b >>= 1;
    }
    return ans;
}

int inv(int a, int m){
    return powm(a, m-2);
}

int C(int n, int r){
    int ans = 1;
    for(int i = 0; i < r; i++){
        ans *= n - i;
        ans %= MOD;
        ans *= inv(i + 1, MOD);
        ans %= MOD;
    }
    return ans;
}

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;

    int ans = 0;
    
    for(int i = 1; i <= n; i++){
        if(n/i >= k){
            ans += C(n/i - 1, k - 1);
            ans %= MOD;
        }
    }

    cout << ans << endl;
}
