#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    int n;
    cin>>n;
    vector<int> a(4);
    for(int i = 0; i<4; i++){
        a[i] = ((1<<i) & n)>>i;
    }
    int ans = 0;
    for(int i = 0; i<4; i++){
        ans += (1<<(3-i)) * a[i];
    }
    ans = ans - 1;
    for(int i = 0; i<4; i++){
        a[i] = ((1<<i) & ans)>>i;
    }
    for(int i=0; i<4; i++){
    }
    ans = 0;
    for(int i = 0; i<4; i++){
        ans += (1<<(3-i)) * a[i];
    }
    cout<<ans;
}