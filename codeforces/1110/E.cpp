#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);int n;
    cin>>n;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i<n; i++) cin>>a[i];
    for(int i = 0; i<n; i++) cin>>b[i];
    vector<int> diff(n-1), diff2(n-1);
    for(int i = 0; i<n-1; i++){
        diff[i] = a[i+1] - a[i];
        diff2[i] = b[i+1] - b[i];
    }
    sort(diff2.begin(), diff2.end());
    sort(diff.begin(), diff.end());
    bool ans = (a[0]==b[0])&&(a[n-1]==b[n-1]);
    for(int i = 0; i<n-1; i++){
        ans = ans&&(diff[i] == diff2[i]);
    }
    if(ans){
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }
}