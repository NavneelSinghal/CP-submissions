#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int maxn = 2e5+1;
int a[maxn] = {0};
int dig(int a){
  int ans = 0; 
  while(a){
    ans++;
    a>>=2;
  }
  return ans;
}
int r = 1e5;
signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, k, m=0;
  map<int, int> cnt;
  	cin >> n >> k;
	for(int i=0;i<=63;i++) if((n >> i) & 1) cnt[i]++, m++;
	if(m > k) return cout << "No" << endl, 0;
	for(int i=63;i>=-63;i--){
		if(m + cnt[i] <= k)
			m += cnt[i], cnt[i - 1] += cnt[i] * 2, cnt[i] = 0;
		else
			break;
	}
	cout << "Yes" << endl;
	multiset<int> ms;
	for(int i=63;i>=-63;i--) for(int j=0;j<cnt[i];j++) ms.insert(i);
	while(ms.size() < k){
		int u = *ms.begin();
		ms.erase(ms.begin());
		ms.insert(u - 1); ms.insert(u - 1);
	}
	for(auto it=ms.rbegin();it!=ms.rend();it++) cout << *it << " ";
	cout << endl;
}