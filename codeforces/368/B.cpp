#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin>>n>>m;
    vector<int> a(n);
    set<int> s;
    int ans[n];
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    for(int i = n-1; i>=0; i--){
        s.insert(a[i]);
        ans[i] = s.size();
    }
    for(int i = 0; i<m; i++){
        int x;
        cin>>x;
        cout<<ans[x-1]<<"\n";
    }
    return 0;
}