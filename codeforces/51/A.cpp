#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll

signed main(){
    int n;
    cin>>n;
    set<string> sd;
    for(int i = 0; i<n; i++){
        string a;
        if(i>0){
            cin>>a;
        }
        string x;
        string y;
        cin>>x>>y;
        reverse(y.begin(), y.end());
        x+=y;
        string s = x;
        for(int i = 0; i<4; i++){
            rotate(x.begin(), x.begin()+1, x.end());
            s = min(s, x);
        }
        sd.insert(s);
        
    }
    cout<<sd.size();
}