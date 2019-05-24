#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    map<string, int> m;
    while(n--){
        string s;
        cin>>s;
        auto search = m.find(s);
        if(search==m.end()){
            m[s]=0;
            cout<<"OK"<<endl;
        }
        if(search!=m.end()){
            m[s]+=1;
            cout<<s<<m[s]<<endl;
        }
    }
}