#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    string x;
    cin>>x>>a>>b;
    int moda = 0;
    vector<int> la;
    for(int i = 0; i<x.size(); i++){
        moda = (moda*10 + x[i]-'0')%a;
        if(moda==0) la.push_back(i+1);
    }
    int modb = 0;
    int pt = 10;
    vector<int> lb;
    for(int i = x.size()-1; i>=0; i--){
        modb = (modb + pt*(x[i]-'0'))%b;
        pt = (pt*10)%b;
        if(modb == 0)
        lb.push_back(i);
    }
    int n = la.size(), m = lb.size();
    reverse(lb.begin(), lb.end());
    int i = 0, j = 0;
    int ans = -1;
    while(i<n and j<m){
        if(la[i]==lb[j]){
            if(x[la[i]]!='0') {ans = la[i];}
            i++; j++;
        }
        else if(la[i]<lb[j]) i+=1;
        else j+=1;
    }
    if (ans == -1 || ans == x.size()) cout<<"NO"<<endl;
    else{
        string left = x.substr(0, ans);
        string right = x.substr(ans);
        //cout<<left<<" "<<right<<" ";
        bool val = right[0] == '0';
        if(val) cout<<"NO"<<endl;
        else cout<<"YES\n"<<left<<"\n"<<right<<"\n";
    }

}