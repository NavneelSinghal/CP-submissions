#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    long long p = 1;
    while(n-5*p>0){
        n = n-5*p;
        p*=2;
    }
    n=(n-1)/p;
    if(n==0){
        cout<<"Sheldon";
    }if(n==1){
        cout<<"Leonard";
    }if(n==2){
        cout<< "Penny";
    }if(n==3){
        cout<<"Rajesh";
    }if(n==4){
        cout<<"Howard";
    }
}