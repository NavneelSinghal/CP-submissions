#include<bits/stdc++.h>
using namespace std;

vector<bool> visited(200005, false);
vector<int> adj[200005];
queue<int> q;
vector<int> v(200005);

bool comp(int x, int y){
    return v[x]<v[y];
}

int main(){
    int n;
    cin>>n;
    for(int i = 0; i<n-1; i++){
        int x, y;
        cin>>x>>y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> w2(n+1);
    for(int i = 0; i<n; i++){
        cin>>w2[i];
        w2[i]--;
        v[w2[i]] = i;
    }
    for(int i = 0; i<n; i++){
        sort(adj[i].begin(), adj[i].end(), comp);
    }
    vector<int> w;
    visited[0] = true;
    q.push(0);
    w.push_back(0);
    while(!q.empty()){
        int x = q.front();
        visited[x] = true;
        q.pop();
        for(auto y : adj[x]){
            if(visited[y]) continue;
            q.push(y);
            w.push_back(y);
        }
    }
    bool ans = true;
    for(int i = 0; i<n; i++){
        ans = ans&(w[i]==w2[i]);
    }
    if(ans){
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }
}