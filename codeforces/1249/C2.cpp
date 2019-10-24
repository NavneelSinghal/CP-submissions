#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(64);
        for(int i = 0; i<64; i++){
            a[i] = n%3;
            n /= 3;
        }
        int ans = 0;
        for(int i = 63; i>=0; i--){
            if(a[i] == 2){
                for(int j = i+1; j < 64; j++){
                    if(a[j] == 0){
                        for(int k = 0; k < j; k++){
                            a[k] = 0;
                        }
                        
                    a[j] = 1;
                    break;
                    }
                }
                break;
            }
        }
        int po = 1;
        for(int i = 0; i<64; i++){
            ans += po * a[i];
            po *= 3;
        }
        cout<<ans<<endl; 
    }
}