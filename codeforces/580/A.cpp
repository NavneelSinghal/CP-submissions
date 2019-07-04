#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    int maxsf = 1;
    int maxfinal = 1;
    for(int i = 1; i<n; i++){
        if(a[i]>=a[i-1]){
            maxsf++;
        }
        else{
            maxsf = 1;
        }
        maxfinal = max(maxfinal, maxsf);
    }
    cout<<maxfinal;
}