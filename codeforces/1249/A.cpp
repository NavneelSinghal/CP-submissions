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
        vector<int> a(101);
        for(int i = 0; i<n; i++){
            int x;
            cin>>x;
            a[x]++;
        }
        bool tw = false;
        for(int i = 0; i<100; i++){
            if(a[i] && a[i+1]){
                tw = true;
            }
        }
        cout<<(tw?2:1)<<endl;
    }
}