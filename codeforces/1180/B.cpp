#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;vector<int> a(n);
    for(int i = 0; i<n; i++){
        cin>>a[i];
        if(a[i]>=0){
            a[i] = -a[i]-1;
        }
    }
    int mn = a[0];
    int idx = 0;
    if(n%2!=0){
        for(int i = 0; i<n; i++){
            if(a[i]<mn){
                idx = i;
                mn = min(mn, a[i]);
            }
        }
        a[idx] = -a[idx] - 1;
    }
    for(int i; i<n; i++){
        cout<<a[i]<<" ";
    }
}