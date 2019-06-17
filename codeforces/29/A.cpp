#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> d(n), x(n);
    for(int i = 0; i<n; i++){
        cin>>x[i]>>d[i];
    }
    bool ans  = false;
    for(int i = 0; i<n; i++){
        int r = x[i]+d[i];
        for(int j = 0; j<n; j++){
            if(x[j]==r){
                if(d[j] == -d[i]){
                    ans = true;
                    break;
                }
            }
        }
    }
    if(ans){
        cout<<"YES";
    }
    else cout<<"NO";
}