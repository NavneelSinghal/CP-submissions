#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
#define sq 350

int a[maxn];
int ans[sq+1][sq+1];

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	int q, x, y;
	while(t--){
		cin >> q >> x >> y;
		if(q == 1){
			a[x] += y;
			for(int i = 1; i <= sq; i++) ans[i][x % i] += y;
		}
		else{
			if(x > sq){
				int sol = 0;
				for(int i = y; i <= maxn; i+=x) sol += a[i];
				cout << sol << "\n";
			}
			else{
				cout << ans[x][y] << "\n";
			}
		}
	}
}
