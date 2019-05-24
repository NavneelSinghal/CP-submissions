#include<bits/stdc++.h>
using namespace std;
int main(){
    long long int n;
    cin>>n;
    long long int a[100005], ans[100005];
    long long int maxi = 0;
    long long int i = 0;
    while(i<n){
        long long int x;
        cin>>x;
        a[x]+=1;
        i+=1;
        maxi = max(maxi, x);
    }
    ans[0] = 0;
    ans[1] = a[1];
    long long int l = 2;
    while(l<=maxi){
        ans[l] = max(ans[l-1], ans[l-2]+a[l]*l);
        l+=1;
    }
    cout<<ans[maxi];
}