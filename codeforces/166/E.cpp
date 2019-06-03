#include<bits/stdc++.h>
using namespace std;
#define mx 1000005
#define mod 1000000007
typedef long long int ll;
#define int ll
signed main(){
    int n;
    cin>>n;
    vector<int> x(n+1), y(n+1);
    x[0]=1;
    y[0]=0;
    for(int i = 1; i<=n; i++){
        x[i] = (3*y[i-1])%mod;
        y[i] = (2*y[i-1]+x[i-1])%mod;
    }
    cout<<x[n];
}
