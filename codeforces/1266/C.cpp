#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int r, c;
	cin >> r >> c;
	if(r == 1 && c == 1) cout << 0 << endl;
	else if(c > 1){
		int a[r][c];
		for(int i = 0; i < c; i++){
			a[0][i] = i+2;
		}
		for(int i = 1; i < r; i++){
			for(int j = 0; j < c; j++){
				a[i][j] = (c+i+1)*a[0][j];
			}
		}
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				cout << a[i][j] << " ";
			}
			cout << "\n";
		}
	}
	else{
		for(int i = 0; i < r; i++){
			cout << i+2 << "\n";
		}
	}
}
