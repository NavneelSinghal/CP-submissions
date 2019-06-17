#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[8][8];
    map<char, int> m;
    m['q'] = 9;
    m['r'] = 5;
    m['b'] = 3;
    m['n'] = 3;
    m['p'] = 1;
    m['Q'] = 9;
    m['R'] = 5;
    m['B'] = 3;
    m['N'] = 3;
    m['P'] = 1;
    m['k'] = m['K'] = 0;
    int x = 0, y = 0;
    for(int i = 0; i<8; i++){
        for(int j=0; j<8; j++){
            cin>>a[i][j];
            if(isupper(a[i][j])){
                x+=m[a[i][j]];
            }
            else if(islower(a[i][j])){
                y+=m[a[i][j]];
            }
        }
    }
    if(x>y){
        cout<<"White";
    }
    if(x<y){
        cout<<"Black";
    }
    if(x==y){
        cout<<"Draw";
    }
}