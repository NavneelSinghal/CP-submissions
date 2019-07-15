#include<bits/stdc++.h>
using namespace std;
int main(){
    int y;
    cin>>y;
    y+=1;
    int fi = y%10, se = (y/10)%10, th = (y/100)%10, fo = (y/1000)%10;
    while(fi == se or se==th or th==fo or fo==fi or fi==th or se==fo){
        y+=1;
        fi = y%10, se = (y/10)%10, th = (y/100)%10, fo = (y/1000)%10;
    }
    cout<<y<<endl;
}