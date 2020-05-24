#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> m >> n;
    vector<int> mark(n+1);
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        for(int j = l; j <= r; j++){
            mark[j] = 1;
        }
    }
    vector<int> v;
    for(int i = 1; i <= n; i++){
        if(!mark[i]){
            v.push_back(i);
        }
    }
    cout << v.size() << endl;
    for(auto x : v) cout << x << " ";
    cout << endl;


}

