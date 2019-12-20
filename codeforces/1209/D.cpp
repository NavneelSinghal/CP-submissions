#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> adj(100001, vector<int>());
vector<int> visited(100001, 0);
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	int n;
	int k;
	cin >> n >> k;
	for(int i = 0; i < k; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	function<void(int)> dfs = [&](int v){
		if(!visited[v]){
			visited[v] = 1;
			for(auto u : adj[v]){
				dfs(u);
			}
		}
	};
	int ans = 0;
	for(int i = 0; i < n; i++){
		ans += !visited[i];
		if(!visited[i]) dfs(i);
	}
	cout << k - n + ans << "\n";
}
