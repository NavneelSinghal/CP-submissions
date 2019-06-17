#include<bits/stdc++.h>
using namespace std;
int main(){
    string a;
    cin>>a;
    vector<int> s;
    int ans = 0;
    int r = 1;
    for(int i = 1; i<a.size(); i++){
        if(a[i]==a[i-1]){
            r++;
        }
        else{
            ans+=ceil(r/5.0);
            r = 1;
        }
    }
    ans+=ceil(r/5.0);
    cout<<ans;
}