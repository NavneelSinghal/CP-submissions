#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin>>n>>m;
    vector<int> a(n), pre(n);
    pre[0] = a[0];
    for(int i = 0; i<n; i++){
        cin>>a[i];
        if(i==0)pre[0] = a[0];
        else{
            pre[i] = pre[i-1]+a[i];
        }
    }
    for(int i = 0; i<n; i++){
        if(pre[i]<=m){
            cout<<"0 ";
        }
        else{
            vector<int> b(i);
            
            for(int j = 0; j<i; j++){
                b[j] = a[j];
            }
            sort(b.begin(), b.end());
            vector<int> preb(i);
            for(int j = 0; j<i; j++){
                preb[0] = b[0];
                if(j>0){
                    preb[j] = preb[j-1]+b[j];
                }
            }
            int j = 0;
            while(j<i && preb[j]+a[i]<=m) j++;
            //int x = lower_bound(preb.begin(), preb.end(), m - a[i]) - preb.begin();
            cout<<i-j<<" ";
        }
    }
}