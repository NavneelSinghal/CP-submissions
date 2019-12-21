#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m;
	cin >> n >> m;
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	sort(a, a+n);
	int ans[n];
	int cur = 0;
	for(int i = 0; i < n; i++){
		cur += a[i];
		ans[i] = cur;
		if(i >= m) ans[i] += ans[i - m];
		cout << ans[i] << " ";
	}
}
