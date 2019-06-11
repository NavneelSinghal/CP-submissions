#include<bits/stdc++.h>
using namespace std;
int dig(int n, int x){
    if(n>(1<<x)){
        return dig(n, x+1)+1;
    }
    return 0;
}
int main(){
    int n;
    cin>>n;
    int ans = dig(n+1, 0);
    cout<<ans;
}