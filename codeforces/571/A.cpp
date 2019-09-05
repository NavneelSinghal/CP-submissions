#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    int a, b, c, l;
    cin>>a>>b>>c>>l;
    int tot = (l+3)*(l+1)*(l+2)/6;
    int rem = 0;
    for(int i = 0; i<=l; i++){
        int r = min(a-b-c+i, l-i);
        int s = min(-a+b-c+i, l-i);
        int t = min(-a-b+c+i, l-i);
        if(r>=0) rem += (r+2)*(r+1)/2;
        if(s>=0) rem += (s+2)*(s+1)/2;
        if(t>=0) rem += (t+2)*(t+1)/2;
    }
    cout<<tot-rem;
}