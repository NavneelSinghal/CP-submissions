#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string a[n];
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    int b[7] = {0};
    int mx = 0;
    for(int j = 0; j<7; j++){
        for(int i=0; i<n; i++){
            b[j]+=a[i][j]-'0';
        }
        mx = max(mx, b[j]);
    }
    cout<<mx;
    return 0;
}