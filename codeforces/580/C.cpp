#include <bits/stdc++.h>

using namespace std;
int m;
vector<vector<int>> adj(100005); 
int ans = 0;
vector<int> cat;
void go(int v, int pr, int k){
    if(k>m) return;
    int l = 1;
    for(int i = 0; i<adj[v].size(); i++){
        if(adj[v][i]!=pr){
            l = 0; 
            go(adj[v][i], v, (k+1)*cat[adj[v][i]]);
        }
    }
    ans += l;
}

int main() {
    int n;
    cin>>n>>m;
    vector<int> v(m);
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        cat.push_back(x);
    }
    for(int i=0; i<n-1; i++){
        int x, y;
        cin>>x>>y;
        adj[x-1].push_back(y-1);adj[y-1].push_back(x-1);
    }
    go(0, -1, cat[0]);
    cout<<ans;
}