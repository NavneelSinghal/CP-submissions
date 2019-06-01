#include <bits/stdc++.h>

using namespace std;

int main() {
    string a;
    cin>>a;
    int ind = -1;
    for(int i = 0; i<a.size()-1; i++){
        if(a[i]=='A'&&a[i+1]=='B'){
            ind = i+1; break;
        }
    }
    if(ind!=-1)
    for(int i = ind+1; i<a.size()-1; i++){
        if(a[i]=='B'&&a[i+1]=='A'){
            cout<<"YES";
            return 0;
        }
    }
    ind = -1;
    for(int i = 0; i<a.size()-1; i++){
        if(a[i]=='B'&&a[i+1]=='A'){
            ind = i+1; break;
        }
    }
    if(ind!=-1)
    for(int i = ind+1; i<a.size()-1; i++){
        if(a[i]=='A'&&a[i+1]=='B'){
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}