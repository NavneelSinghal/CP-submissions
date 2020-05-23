#include <bits/stdc++.h>
using namespace std;
     
struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;
 
    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }
 
    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }
 
    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }
     
    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;
 
        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }
 
    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};
     
const int MAXN = 2e5 + 5;
int d[MAXN];

void dfs2(vector<vector<int>> &g, int u, int p) {
   if(u == 0) d[u] = 0;
   else d[u] = d[p] + 1;
   for(int v : g[u]) {
      if(v == p) continue;
      dfs2(g, v, u);
   }
}
     
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
     
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    set<pair<int, int>> par;
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
        par.insert({u, v});
        par.insert({v, u});
    }
     
    dfs2(g, 0, -1);
     
    LCA lca(g);
    for(int q = 0; q < m; ++q) {
        int k;
        cin >> k;
        bool ans = true;
        int vers[k];
        int ver = 0;
        for(int i = 0; i < k; ++i) {
            cin >> vers[i];
            vers[i]--;
            if(i == 0) ver = vers[i];
            if(d[vers[i]] > d[ver]) ver = vers[i];
        }
     
        for(int i = 0; i < k; ++i) {
            if(lca.lca(ver, vers[i]) == vers[i] || par.count({lca.lca(ver, vers[i]), vers[i]})) continue;
            ans = false;
        }
        if(ans) cout << "YES\n";
        else cout << "NO\n";
    }
}

