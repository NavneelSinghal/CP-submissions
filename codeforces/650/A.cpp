#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define int ll
signed main(){
    int n;
    cin>>n;
    int ans = 0;
    map<int, int> m1, m2;
    map< pair <int, int>, int> mn;
    for(int i = 0; i<n; i++){
        int x, y;
        cin>>x>>y;
        ans += m1[x]++ + m2[y]++ - mn[make_pair(x, y)]++;
    }
    cout<<ans;
}