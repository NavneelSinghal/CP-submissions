#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> l(n), r(n), a(n);
    for(int i = 0; i<n; i++){
        cin>>l[i];
    }
    for(int i = 0; i<n; i++){
        cin>>r[i];
        a[i] = n-l[i]-r[i];
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<i; j++){
            if(a[j]>a[i]){
                l[i]--;
            }
        }
        for(int j = i+1; j<n; j++){
            if(a[j]>a[i]){
                r[i]--;
            }
        }
    }
    for(int i = 0; i<n; i++){
        if(l[i]!=0 || r[i]!=0){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES\n";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
}