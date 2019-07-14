#include<bits/stdc++.h>
using namespace std;
#define MAX 1e9
int main(){
    int a1, b1, a2, b2, a3, b3;
    cin>>a1>>b1>>a2>>b2>>a3>>b3;
    int c1 = max(a2, a3), d1 = b2+b3;
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    c1 = a2+a3, d1 = max(b2,b3);
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    
    swap(a2, b2);
    
     c1 = max(a2, a3), d1 = b2+b3;
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    c1 = a2+a3, d1 = max(b2,b3);
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    
    swap(a2, b2); swap(a3, b3);
    
     c1 = max(a2, a3), d1 = b2+b3;
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    c1 = a2+a3, d1 = max(b2,b3);
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    
    swap(a2, b2);
    
     c1 = max(a2, a3), d1 = b2+b3;
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    c1 = a2+a3, d1 = max(b2,b3);
    if(c1<=a1 && d1<=b1) {cout<<"YES"; return 0;}
    
    cout<<"NO";
    return 0;
}
