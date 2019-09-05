#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int,int>
signed main(){
    int k;
    cin>>k;
    int n = 1<<k;
    int a[n][n];
    a[0][0]=1;
    for(int i = 0; i<k; i++){
        for(int j = 0; j<(1<<i); j++){
            for(int l = 0; l<(1<<i); l++){
                a[l+(1<<i)][j] = -a[l][j];
                a[l][j+(1<<i)] = -a[l][j];
                a[l+(1<<i)][j+(1<<i)] = -a[l][j];
            }
        }
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(a[i][j]==1) cout<<"*";
            else cout<<"+";
        }cout<<"\n";
    }
}