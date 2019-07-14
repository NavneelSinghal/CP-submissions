#include<bits/stdc++.h>
using namespace std;
#define MAX 1e9
int main(){
    int n;
    cin>>n;
    vector<pair<int, int> > pos, neg;
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        int a;
        cin>>a;
        if(x>0){
            pos.push_back({x, a});
        }
        else{
            neg.push_back({x, a});
        }
    }
    int r = min(pos.size(), neg.size());
    sort(pos.begin(), pos.end());
    sort(neg.rbegin(), neg.rend());
    int ans = 0;
    for(int i = 0; i<r; i++){
        ans += pos[i].second + neg[i].second;
    }
    if(neg.size()>pos.size()){
        ans += neg[pos.size()].second;
    }
    if(neg.size()<pos.size()){
        ans += pos[neg.size()].second;
    }
    cout<<ans;
    return 0;
}
