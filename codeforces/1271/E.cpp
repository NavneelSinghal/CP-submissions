#include <bits/stdc++.h>
using namespace std;

#define int long long
#define REP(i, n) for(int i = 0; i < (int) n; i++)

signed main() {
	int n, k;
	cin >> n >> k;
	if(n == k) cout << 1 << "\n";
	else if(k == 1) cout << n << "\n";
	else if(((k+1)&k)==0){
		if(n % (k+1) == k){
			cout << 2 * ((n-k)/(k+1)) + 1 << "\n";
		}
		else{
			cout << 2 * (n/(k+1)) << "\n";
		}
	}
	else{
		int po = 1;
		while((1ll<<po) <= k){
			po++;
		}
		po--;
		cout << (1 + (n-k-1)/(1ll<<po))*2 << "\n";
	}
}
