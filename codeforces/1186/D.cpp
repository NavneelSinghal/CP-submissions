#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    double a[n];int b[n];
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    for(int i = 0; i<n; i++){
        b[i] = floor(a[i]);
    }
    int sum  = 0;
    for(int i = 0; i<n; i++){
        sum += b[i];
    }
    for(int i = 0; i<n && sum!=0; i++){
        if(!(a[i]==b[i])){
            b[i]++;
            sum++;
        }
    }
    for(int i = 0; i<n; i++){
        cout<<b[i]<<"\n";
    }
    return 0;
}