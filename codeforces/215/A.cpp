#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n); 
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    int m;
    cin>>m;
    vector<int> b(m);
    for(int i = 0; i<m; i++){
        cin>>b[i];
    }
    int mx = 0;
    int ans = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(b[j]%a[i]==0){
                mx = max(mx, b[j]/a[i]);
            }
        }
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(b[j]%a[i]==0 && mx == b[j]/a[i]){
                ans++;
            }
        }
    }
    cout<<ans;
}