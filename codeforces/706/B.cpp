#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> price(n);
    for(int i=0; i<n; i++){
        cin>>price[i];
    }
    int q;
    cin>>q;
    vector<int> money(q);
    for(int i=0; i<q; i++){
        cin>>money[i];
    }
    sort(price.begin(), price.end());
    for(int i=0; i<q; i++){
        auto x = upper_bound(price.begin(), price.end(), money[i]);
        int ans = x-price.begin();
        cout<<ans<<endl;
    }
}