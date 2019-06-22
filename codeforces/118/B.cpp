#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i = 0; i<=n; i++){
        if(i!=0){
            cout<<endl;
        }
        for(int j = 0; j<2*(n-i); j++){
            cout<<" ";
        }
        cout<<"0";
        for(int j = 1; j<=i; j++){
            cout<<" "<<j;
        }
        for(int j = i-1; j>=0; j--){
            cout<<" "<<j;
        }
        
        
    }
    for(int i = n-1; i>=0; i--){
        cout<<endl;
        for(int j = 0; j<2*(n-i); j++){
            cout<<" ";
        }
        cout<<"0";
        for(int j = 1; j<=i; j++){
            cout<<" "<<j;
        }
        for(int j = i-1; j>=0; j--){
            cout<<" "<<j;
        }
    }
}