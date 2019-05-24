#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n, a, b, c;
    cin>>n>>a>>b>>c;
    int d[10000];
    d[a]=1;
    d[b]=1;
    d[c]=1;
    for(long long int i = 1; i<=n; ++i){
        if(a!=b && b!=c && c!=a){
            d[i+a] = max(d[i+a], d[i]!=0?d[i]+1:0);
            d[i+b] = max(d[i+b], d[i]!=0?d[i]+1:0);
            d[i+c] = max(d[i+c], d[i]!=0?d[i]+1:0);
        }
        else if(a==b && b==c){
            d[i+a] = max(d[i+a], d[i]!=0?d[i]+1:0);
        }
        else if(a==b){
            d[i+b] = max(d[i+b], d[i]!=0?d[i]+1:0);
            d[i+c] = max(d[i+c], d[i]!=0?d[i]+1:0);
        }
        else if(b==c){
            d[i+b] = max(d[i+b], d[i]!=0?d[i]+1:0);
            d[i+a] = max(d[i+a], d[i]!=0?d[i]+1:0);
        }
        else if(a==c){
            d[i+b] = max(d[i+b], d[i]!=0?d[i]+1:0);
            d[i+c] = max(d[i+c], d[i]!=0?d[i]+1:0);
        }
    }
    cout<<d[n];
}