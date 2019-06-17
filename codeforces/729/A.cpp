#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string a;
    cin>>a;
    string ans;
    for(int i = 0; i<n; i++){
        if(a[i]=='o'&&a[i+1]=='g'&&a[i+2]=='o'&&i+2<n){
            while(a[i+1]=='g'&&a[i+2]=='o'&&i+2<n){
                i+=2;
            }
            ans += "***";
        }
        else{
            ans+=a[i];
        }
    }
    cout<<ans;
}