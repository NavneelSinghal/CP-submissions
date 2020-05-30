#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

void dfs(vector<vector<int>> &g, int u, int col, vector<int> &vis){
    vis[u] = col;
    for(auto v : g[u]){
        if(vis[v] == 0){
            dfs(g, v, 3 - col, vis);
        }
    }
}

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int u, v1;
        vector<vector<int>> g(n);
        for(int i = 0; i < m; i++){
            cin >> u >> v1;
            --u, --v1;
            g[u].push_back(v1);
            g[v1].push_back(u);
        }
        vector<int> vis(n);
        dfs(g, 0, 1, vis);
        vector<vector<int>> cols(2);
        for(int i = 0; i < n; i++){
            cols[vis[i] - 1].push_back(i);
        }
        vector<int> v;
        if(cols[0].size() >= cols[1].size()) v = cols[1];
        else v = cols[0];
        cout << v.size() << "\n";
        for(auto &x : v) cout << x + 1 << " ";
        cout << "\n";
    }
}
