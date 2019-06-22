#include<bits/stdc++.h>
using namespace std;
int main(){
    long long int a, b, s;
    cin>>a>>b>>s;
    if(abs(a)+abs(b)<=s && (s-a-b)%2==0){
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }
}