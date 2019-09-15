#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i = 0; i<n; i++) cin>>a[i];
    sort(a, a+n);
    vector<bool> coloured(n, false);
    int col = 0;
    for(int i = 0; i<n; i++){
        if(!coloured[i]){
            col++;
            for(int j = i; j<n; j++){
                if(a[j]%a[i]==0){
                    coloured[j] = true;
                }
            }
        }
    }
    cout<<col;
}