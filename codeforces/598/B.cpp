#include <bits/stdc++.h>
using namespace std;

#define int long long
#define REP(i, n) for(int i = 0; i < (int) n; i++)

signed main() {
	string s;
	cin>>s;
	int m;
	cin >> m;
	REP(_, m){
		int l, r, k;
		cin >> l >> r >> k;
		--l, --r;
		string w = s.substr(l, r-l+1);
		//cout << s << " " << w << "\n";
		REP(i, r-l+1){
			s[i+l] = w[(i-k%(r-l+1)+3*(r-l+1))%(r-l+1)];
		}
	}
	cout << s << "\n";
}
