#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    long long ans = -1;
    long long mini = 100000, maxi = -1;
    for(long long i=0; i<n; i+=1){
        long long x;
        cin>>x;
        if(mini>x){
            ans+=1;
        }
        else if(maxi<x){
            ans+=1;
        }
        mini = min(mini, x);
        maxi = max(maxi, x);
    }
    cout<<ans;
}