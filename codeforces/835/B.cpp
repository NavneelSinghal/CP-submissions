#include<bits/stdc++.h>
using namespace std;
    
    int k;
    string n;
    int cnt[10];
    int sum = 0;
    
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin>>k>>n;
    for(int i = 0; i<n.size(); i++){
        int d = n[i]-'0';
        cnt[d]++;
        sum += d;
    }
    int ans = 0;
    for(int i = 0; i<10; i+=1){
        for(int j = 0; j<cnt[i]; j++){
            if(sum < k){
                sum += 9-i;
                ans+=1;
            }
        }
    }
    cout<<ans;
}
