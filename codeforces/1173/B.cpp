#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<(n/2)+1<<endl;;
    int a = 1, b = 1;
    int p = 1;
    for(int i = 0; i<n; i++){
        cout<<a<<" "<<b<<endl;
        p*=-1;
        if(p==-1){
            b+=1;
        }
        else a+=1;
    }
}