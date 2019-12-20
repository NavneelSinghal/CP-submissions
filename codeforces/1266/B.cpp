#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	while(n--){
		int x;
		cin >> x;
		if(x <= 14 || x%14 >= 7 || x%14 == 0){
			cout << "NO\n";
		}
		else{
			cout << "YES\n";
		}
	}
}
