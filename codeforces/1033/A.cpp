#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int ax, ay, bx, by, cx, cy;
    cin>>ax>>ay>>bx>>by>>cx>>cy;
    bx-=ax;
    cx-=ax;
    by-=ay;
    cy-=ay;
    if(bx*cx>0 && by*cy>0){
        cout<<"YES";
    }
    else cout<<"NO";
}