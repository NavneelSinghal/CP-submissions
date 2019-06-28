#include<bits/stdc++.h>
using namespace std;
int main(){
    int ans = 0;
    string a, b;
    cin>>a>>b;
    int la = a.size();
    int lb = b.size();
    int init = 0;
    for(int i = 0; i<lb; i++){
        init += (a[i]!=b[i]);
    }
    ans = init%2==0 ? 1:0;
    
    vector<int> v(la-1);
    for(int i = 0; i<la-1; i++){
        v[i] = a[i]!=a[i+1] ? 1 : 0;
    }
    int pre[la]; //1 indexed
    pre[0] = 0;
    for(int i = 1; i<la; i++){
        pre[i] = pre[i-1]+v[i-1];
    }
    for(int i = 0; i<la-lb; i++){
        init += pre[i+lb] - pre[i];
        init = (init+2)%2;
        if(!init){
            ans++;
        }
    }
    cout<<ans;
}