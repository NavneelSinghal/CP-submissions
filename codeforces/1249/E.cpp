#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int n, c;
    cin>>n>>c;
    vector<int> a(n-1), b(n-1);
    for(int i = 0; i<n-1; i++){
        cin>>a[i];
    }
    for(int i = 0; i<n-1; i++){
        cin>>b[i];
    }
    vector<int> dp[2];
    for(int i = 0; i<2; i++) dp[i].resize(n);
    for(int i = 0; i<n; i++) for(int j = 0; j < 2; j++) dp[j][i] = 1e18;
    dp[0][0] = 0, dp[1][0] = c;
    for(int i = 0; i<n-1; i++){
        dp[0][i+1] = min(dp[1][i]+a[i], min(dp[0][i+1], dp[0][i]+a[i]));
        dp[1][i+1] = min(dp[1][i]+b[i], min(dp[1][i+1], dp[0][i]+b[i]+c));
    }
    for(int i = 0; i<n; i++) cout<<min(dp[0][i], dp[1][i])<<" ";
}