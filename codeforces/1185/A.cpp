#include<bits/stdc++.h>
using namespace std;
int main(){
    int a, b, c, d;
    cin>>a>>b>>c>>d;
    int x[3];
    x[0]=a;
    x[1]=b;
    x[2]=c;
    sort(x, x+3);
    cout<<max(x[0]-x[1]+d, 0)+max(x[1]+d-x[2], 0);
}