#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int n, s, t;
        cin>>n>>s>>t;
        cout<<min(max(n-s, n-t)+1, 2*n - s - t + 1)<<"\n";
    }
}