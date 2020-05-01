#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int left = 0, right = 0;
        for(int i = 1; i < n/2; i++){
            left += (1LL << i);
        }
        for(int i = n/2; i < n; i++){
            right += (1LL << i);
        }
        left += (1LL << n);
        cout << (left - right) << endl;
    }
}