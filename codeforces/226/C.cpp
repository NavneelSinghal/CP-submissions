#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>

#define FAST_IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define PRECISION(x) cout<<fixed<<setprecision(x);
#define int long long

using namespace std;

map<int, int> memo;

int fib(int n, int &m){
    if(n <= 2) return 1%m;
    if(memo.count(n)) return memo[n];
    int k = (n + 1) / 2;
    int ret = fib(k, m) * fib(n - k + 1, m) + fib(k - 1, m) * fib(n - k, m);
    ret %= m;
    memo[n] = ret;
    return ret;
}

bool nums(int l, int r, int k, int w){
    return r/w - (l-1)/w >= k;
}

void solve(){
	int m, l, r, k;
	cin >> m >> l >> r >> k;
	//gcd(f_a, f_b) = f_gcd(a, b)
	//so we need to find largest gcd of all k element subsets
	//so we need to find the largest number which divides
	//at least k numbers in [l,r]
	int ans = 1;
    for(int i = 1; i * i <= r; i++){
        if(nums(l, r, k, i)) ans = max(ans, i);
        if(nums(l, r, k, r/i)) ans = max(ans, r/i);
    }
	//now we need to find f_ans
	cout << fib(ans, m) % m << "\n";
}

signed main(){
	FAST_IO
	PRECISION(10)
	int t = 1;
	while(t--){
		solve();
	}
}

