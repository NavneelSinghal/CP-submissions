#include<bits/stdc++.h>
using namespace std;
int main(){
    int x, y, z;
    cin>>x>>y>>z;
    int res = x-y;
    if(res - z > 0){
        cout<<"+";
    }
    else if(res + z<0){
        cout<<"-";
    }
    else if(z == 0){
        if(res==0){
            cout<<"0";
        }
    }
    else{
        cout<<"?";
    }
}