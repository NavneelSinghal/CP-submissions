#include<bits/stdc++.h>
using namespace std;
int main(){
    
    int n, m;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    int up = 1, down = n;
    while(up<down){
        for(int i = 1; i<=m; i++){
            cout<<up<<" "<<i<<"\n";
            cout<<down<<" "<<m+1-i<<"\n";
        }
        up++, down--;
    }
    if(up == down){
        int i = 1;
        int cnt = 0;
        int parity = 0;
        while(cnt!=m){
            cnt++;
            cout<<up<<" "<<i<<"\n";
            i = m+1+parity-i;
            parity = 1-parity;
        }
    }
}