#include<bits/stdc++.h>
using namespace std;
bool iss(vector<int> a){
    bool an = true;
    for(int i = 0; i<a.size()-1; i++){
        an = an && (a[i]<=a[i+1]);
    }
    return an;
}
int ans(vector<int> a){
    if(iss(a)){
        return a.size();
    }
    else{
        vector<int> x, y;
        for(int i = 0; i<a.size()/2; i++){
            x.push_back(a[i]);
        }
        for(int i = 0+a.size()/2; i<a.size(); i++){
            y.push_back(a[i]);
        }
        return max(ans(x), ans(y));
    }
}
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    cout<<ans(a);
}