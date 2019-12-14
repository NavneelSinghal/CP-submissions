#pragma GCC optimize("Ofast")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define int long long 
#define double long double
#define vi vector<int>
#define pb push_back
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(v.begin(), v.end(), RNG);
using namespace std;

vi adj[(int)2e5+5];
int visited[(int)2e5+5];

void dfs(int a, int b){
	if(!visited[a]){
		visited[a] = 1;
		for(auto u : adj[a]){
			if(visited[u] != 1 && u != b){
				dfs(u, b);
			}
		}
	}
}

signed main(){
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
	cout<<fixed<<setprecision(1);
	
	int t;
	cin>>t;
	int n, m, a, b;
	while(t--){
		cin>>n>>m>>a>>b;
		fill(adj, adj+n, vi(0));
		fill(visited, visited+n, 0);
		--a, --b;
		REP(_, m){
			int u, v;
			cin>>u>>v;
			--u, --v;
			adj[v].pb(u);
			adj[u].pb(v);
		}
		dfs(a, b);
		set<int> visa, visb;
		for(int i = 0; i < n; i++){
			if(visited[i]) visa.insert(i);
		}
		fill(visited, visited+n, 0);
		dfs(b, a);
		for(int i = 0; i < n; i++){
			if(visited[i]) visb.insert(i);
		}
		visa.erase(a);
		visb.erase(b);
		vi store(n);
		auto it1 = set_difference(visa.begin(), visa.end(), visb.begin(), visb.end(), store.begin());
		int a1 = it1 - store.begin();
		it1 = set_difference(visb.begin(), visb.end(), visa.begin(), visa.end(), store.begin());
		int b1 = it1 - store.begin();
		cout<<a1*b1<<"\n";
	}
}
