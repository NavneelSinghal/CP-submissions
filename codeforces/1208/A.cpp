#pragma GCC optimize("Ofast")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;


#define int long long 
#define double long double
#define vi vector<int>
#define pb push_back
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(v.begin(), v.end(), RNG);
using namespace std;

signed main(){
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
	cout<<fixed<<setprecision(1);
	int t;
	cin>>t;
	while(t--){
		int n, a, b;
		cin>>a>>b>>n;
		if(n%3==0) cout<<a<<"\n";
		else if(n%3==1) cout<<b<<"\n";
		else cout<<(a^b)<<"\n";
	}
}
