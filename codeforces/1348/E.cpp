#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
    int n, k;
    cin >> n >> k;
    int t = 0;
    bool dp[510][510];
    int a[510], b[510];
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
    }
    for(int i = 0; i < n; i++){
        t += a[i] + b[i];
    }
    dp[0][0] = true;
    for(int i = 1; i < n + 1; i++){
        for(int j = 0; j < k; j++){
            dp[i][j] = dp[i - 1][(j - a[i - 1] % k + k) % k];
            for(int w = 0; w < min(k, a[i - 1] + 1); w++){
                if((a[i - 1] - w) % k + b[i - 1] >= k){
                    dp[i][j] |= dp[i - 1][(j - w + k) % k];
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < k; i++){
        if(dp[n][i]){
            ans = max(ans, (t - i)/k);
        }
    }
    cout << ans << endl;
}
