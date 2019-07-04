#include<bits/stdc++.h>
using namespace std;
int main(){
    int a;
    int b;
    cin>>a>>b;
    int ans = 0;
    while(a>=b){
        ans += (a/b)*b;
        a = (a/b) + (a%b);
    }
    ans += a;
    cout<<ans;
    return 0;
}