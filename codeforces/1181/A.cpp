#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    int x, y, z;
    cin>>x>>y>>z;
    cout<<(x+y)/z<<" ";
    int r = x/z;
    int s = y/z;
    int r1 = x%z;
    int r2 = y%z;
    if(r+s==(x+y)/z){
        cout<<0;
    }
    else{
        cout<<min((z-r1)%z, (z-r2)%z);
    }
}