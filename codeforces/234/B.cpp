#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    cin>>n>>k;
    vector<pair<int, int> > a;
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        a.push_back({x, i+1});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    cout<<a[k-1].first<<"\n";
    for(int i = 0; i<k; i++){
        cout<<a[i].second<<" ";
    }
    return 0;
}