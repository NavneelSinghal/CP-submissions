#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	while(n--){
		string a;
		cin >> a;
		int cnt0 = 0, sum = 0, cnt2 = 0;
		for(auto c : a) if(c == '0') cnt0++; else if((c - '0')%2 == 0) cnt2++;
		for(auto c : a){
			sum += c - '0';
		}
		if(sum % 3 == 0){
			if(cnt0 == 0 || (cnt0 == 1 && cnt2 == 0 && a.size() != 1)){
				cout << "cyan\n";
			}
			else{
				cout << "red\n";
			}
		}
		else{
			cout << "cyan\n";
		}
	}
}
