#include<bits/stdc++.h>
using namespace std;
int main(){
    string w;
    cin>>w;
    for(int i=0; i<w.length(); i++){
        if(tolower(w[i])==('a')||tolower(w[i])==('e')||tolower(w[i])==('i')||tolower(w[i])==('o')||tolower(w[i])==('u')||tolower(w[i])==('y')){
        }
        else{
            cout<<"."<<char(tolower(w[i]));
        }
    }
    return 0;
}