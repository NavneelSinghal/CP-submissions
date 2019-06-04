#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define int ll
signed main(){
    int n, l, r, x;
    cin>>n>>l>>r>>x;
    int ans = 0;
    int a[15];
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    sort(a, a+n);
    int p = 1<<n;
    for(int i = 0; i< p; i++){
        vector<int> v;
        for(int j = 0; j<n; j++){
            if(i & 1<<j){
                v.push_back(a[j]);
            }
        }
        int l1 = v.size();
        if(l1>=2){
        int sum = 0;
        for(int j = 0; j<l1; j++){
            sum+=v[j];
        }
        if((sum<=r) && (sum>=l) && ((v[l1-1]-v[0])>=x)){
            ans += 1;
        }}
    }
    cout<<ans;
}