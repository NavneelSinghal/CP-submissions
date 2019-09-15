#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> sgn(n+1,1);
    for(int i = 0; i<n; i++){
        cin>>a[i];
        sgn[i+1] = sgn[i]*abs(a[i])/a[i];
        //cout<<sgn[i+1]<<" ";
    }
    //cout<<endl;
    int dp[n+1];
    dp[0] = 0;
    
    for(int i = 0; i<n; i++){
        dp[i+1] = dp[i] + (sgn[i+1]==-1); //dp[i] is number of elements that are negative till i
    }
    
    //negative till a[i]
    int ans = 0;
    for(int i = 1; i<=n; i++){
        if(sgn[i] == 1){
            ans += dp[i];
        }
        else{
            ans += i +1- dp[i];
        }
    }
    cout<<ans<<" "<<n*(n+1)/2-ans;
    
}