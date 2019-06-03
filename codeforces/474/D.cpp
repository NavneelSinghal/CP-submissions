#include<bits/stdc++.h>
using namespace std;
#define mx 1000005
#define mod 1000000007
typedef long long int ll;
#define int ll
signed main(){
    int t;
    int k;
    cin>>t>>k;
    int a[mx], s[mx];
    a[0]=1;
    for(int i = 1; i<mx; i++){
        if(i>=k) a[i] = a[i-k] + a[i-1];
        else a[i] = a[i-1];
        if(a[i]>mod) a[i]-=mod;
    }
    s[0] = 0;
    for(int i = 1; i<mx; i++){
        s[i]=s[i-1]+a[i];
    }
    while(t--){
        int a, b;
        cin>>a>>b;
        cout<<(s[b]-s[a-1]+mod)%mod<<endl;
    }
}
