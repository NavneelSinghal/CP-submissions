#include <bits/stdc++.h>
using namespace std;

#define int long long
#define REP(i, n) for(int i = 0; i < (int) n; i++)
#define INF 1000000000

int ans[31][31][51];

int solve(int n, int m, int k){
	if(ans[n][m][k]!=0 || k == 0 || n*m == k){
		return ans[n][m][k];
	}
	int a = INF;
	for(int i = 1; 2*i <= n; i++){
		REP(j, k+1){
			a = min(a, m*m + solve(i, m, k-j) + solve(n-i, m, j));
		}
	}
	for(int i = 1; 2*i <= m; i++){
		REP(j, k+1){
			a = min(a, n*n + solve(n, m-i, k-j) + solve(n, i, j));
		}
	}
	ans[n][m][k] = a;
	return a;
}

signed main() {
	int t;
	cin >> t;
	while(t--){
		int n, m, k;
		cin >> n >> m >> k;
		cout << solve(n, m, k) << "\n";
	}
}
