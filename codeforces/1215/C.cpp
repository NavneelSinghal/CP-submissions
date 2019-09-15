#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int n;
    cin>>n;
    string A, B;
    cin>>A>>B;
    vector<int> a(n), b(n);
    for(int i = 0; i<n; i++){
        a[i] = A[i] - 'a';
        b[i] = B[i] - 'a';
    }
    vector<int> pos1, pos0;
    int balance = 0;
    for(int i = 0; i<n; i++){
        if(a[i]!=b[i]){
            if(a[i]==1) pos1.push_back(i);
            else pos0.push_back(i);
        }
    }
    if((pos0.size()+pos1.size())%2 != 0){
        cout<<-1;
    }
    else{
        cout<<(pos1.size()+pos0.size())/2 + pos1.size()%2<<"\n";
        for(int i = 0; i+1<pos0.size(); i+=2){
            cout<<pos0[i]+1<<" "<<pos0[i+1]+1<<"\n";
        }
        for(int i = 0; i+1<pos1.size(); i+=2){
            cout<<pos1[i]+1<<" "<<pos1[i+1]+1<<"\n";
        }
        if(pos1.size()%2 == 1){
            cout<<pos0.back()+1<<' '<<pos0.back()+1<<endl;
            cout<<pos0.back()+1<<' '<<pos1.back()+1<<endl;
        }
    }
}