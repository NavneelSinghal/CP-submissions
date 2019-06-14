#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    int m = -1;
    for(int i = 0; i<n; i++){
        cin>>a[i];
        if(a[i]>m+1){
            cout<<i+1;
            return 0;
        }
        else{
            m = max(m, a[i]);
        }
    }
    cout<<-1;
    return 0;
}