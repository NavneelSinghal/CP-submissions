#include<bits/stdc++.h>
using namespace std;
string least(string &a){

    if(a.size()%2) return a;
    else{
        string s1 = (a.substr(0, a.size()/2));
        string s2 = (a.substr(a.size()/2, a.size()/2));
        s1 = least(s1);
        s2 = least(s2);
        if(s1<s2){
            return s1+s2;
        }
        else return s2+s1;
    }
}
int main(){
    string a, b;
    cin>>a>>b;
    int n = a.size();
    if(least(a) == least(b)){
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
}
