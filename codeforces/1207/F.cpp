#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
#define sq 275

int a[maxn];
int ans[sq+1][sq+1];
int t, q, x, y, i, sol;

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> t;
	while(t--){
		cin >> q >> x >> y;
		if(q == 1){
			a[x] += y;
			for(i = 1; i <= sq; i++) ans[i][x % i] += y;
		}
		else{
			if(x > sq){
				sol = 0;
				for(i = y; i <= maxn; i+=x) sol += a[i];
				cout << sol << "\n";
			}
			else{
				cout << ans[x][y] << "\n";
			}
		}
	}
}
