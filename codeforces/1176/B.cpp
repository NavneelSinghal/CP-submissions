#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(3);
        for(int i = 0; i<n; i++){
            int x;
            cin>>x;
            x%=3;
            a[x]++;
        }
        if(a[1]==a[2]){
            cout<<a[0]+a[1]<<endl;
        }
        else if(a[1]<a[2]){
            cout<<a[0]+a[1]+(a[2]-a[1])/3<<endl;
        }
        else{
            cout<<a[0]+a[2]+(a[1]-a[2])/3<<endl;
        }
    }
}