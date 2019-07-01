#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> a(n);
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    vector<int> g;
    for(int i = 1; i<n; i++){
        g.push_back(a[i]-a[i-1]);
    }
    sort(g.rbegin(), g.rend());
    int ans = a.back() - a[0];
    for(int i = 0; i<min(k-1, (int) g.size()); i++){
        ans -= g[i];
    }
    cout<<ans+k;
}