#include<bits/stdc++.h>
using namespace std;

void fastscan(int &number) 
{  
    bool negative = false; 
    register int c; 
  
    number = 0; 

    c = getchar(); 
    if (c=='-') 
    { 
        negative = true; 
        c = getchar(); 
    } 

    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 

    if (negative) 
        number *= -1; 
} 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    fastscan(n);
    int a[n];
    for(int i = 0; i<n; i++){
        fastscan(a[i]);
    }
    int maxsf = 1;
    int maxfinal = 1;
    for(int i = 1; i<n; i++){
        if(a[i]>=a[i-1]){
            maxsf++;
        }
        else{
            maxsf = 1;
        }
        maxfinal = max(maxfinal, maxsf);
    }
    cout<<maxfinal;
}