#include<bits/stdc++.h>
using namespace std;
#define maxn 1299710
typedef long long ll;
#define int ll
signed main(){
    int n, m;
    cin>>n>>m;
    vector<pair<int, int> > v;
    for(int i = 1; i<=n && v.size()<m; i++){
        for(int j = i+1; j<=n && v.size()<m; j++){
            if(__gcd(i, j) == 1){
                v.push_back({i, j});
            }
        }
    }
    if(m<n-1 || v.size()!=m){
        cout<<"Impossible";
    }
    else{
        cout<<"Possible\n";
        for(int i = 0; i<m; i++){
            cout<<v[i].first<<" "<<v[i].second<<"\n";
        }
    }
    return 0;
}