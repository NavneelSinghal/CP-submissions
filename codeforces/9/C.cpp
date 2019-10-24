#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int n;
    cin>>n;
    vector<string> v;
    for(int i = 1; i<=1024; i++){
        int j = i;
        string a;
        while(j){
            a += (char)(j%2 + '0');
            j/=2;
        }
        reverse(a.begin(), a.end());
        v.push_back(a);
    }
    int ans = 0;
    for(auto w : v){
        if(stoll(w) <= n){
            ans++;
        }
    }
    cout<<ans<<endl;
}