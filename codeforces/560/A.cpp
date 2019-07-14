#include<bits/stdc++.h>
using namespace std;
#define MAX 1e9
int main(){
    int n;
    cin>>n;
    int ans = MAX;
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        if(x < ans) ans = x;
    }
    if(ans == 1) cout<<-1;
    else cout<<1;
    
}
