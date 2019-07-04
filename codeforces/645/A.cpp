#include<bits/stdc++.h>
using namespace std;
int main(){
    char x[2][2];
    char y[2][2];
    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            cin>>x[i][j];
        }
    }
    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            cin>>y[i][j];
        }
    }
    string s;
    if(x[0][0]!='X'){
        s+=x[0][0];
    }
    if(x[0][1]!='X'){
        s+=x[0][1];
    }
    if(x[1][1]!='X'){
        s+=x[1][1];
    }
    if(x[1][0]!='X'){
        s+=x[1][0];
    }
    string t;
    if(y[0][0]!='X'){
        t+=y[0][0];
    }
    if(y[0][1]!='X'){
        t+=y[0][1];
    }
    if(y[1][1]!='X'){
        t+=y[1][1];
    }
    if(y[1][0]!='X'){
        t+=y[1][0];
    }
    for(int i = 0; i<3; i++){
        rotate(s.begin(), s.begin()+1, s.end());
        if(s==t){
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}