#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin>>q;
    while(q--){
        int n;
        cin>>n;
        
        if((n&(n+1))){
            int ans = 1;
            while(n>=ans){
                ans<<=1;
            }
            cout<<ans-1<<endl;
        }
        else{
            int j = 1;
            for(int i = 2; i*i <= n; i++){
                if(n%i == 0){
                    j = n/i;
                    break;
                }
            }
            cout<<j<<endl;
        }
    }
}