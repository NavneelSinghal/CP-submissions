#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin>>n>>m;
    if(n>=m){
        cout<<n-m;
        return 0;
    }
    else{
        int ans = 0;
        while(n<m) n*=2, ans++;
        int k = n-m;
        int c = ans;
        while(k){
            if((1<<c) <= k){
                k-=(1<<c);
                ans++;
            }
            else c--;
        }
        cout<<ans;
    }
}