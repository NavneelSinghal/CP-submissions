#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

#define vec vector
#define arr array
#define pr pair
#define tp tuple
#define str string
#define pb push_back
#define eb emplace_back
#define rep(i, a, b, inc) for (int i = int(a); i <= int(b); i += int(inc))
#define repl(i, a, b, inc) for (ll i = ll(a); i <= ll(b); i += ll(inc))
#define repd(i, a, b, inc) for (int i = int(a); i >= (b); i -= int(inc))
#define repdl(i, a, b, inc) for (ll i = ll(a); i >= ll(b); i -= ll(inc))
#define all(v) begin(v), end(v)
#define each(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto &&[x, y] : v)
#define each3(x, y, z, v) for (auto &&[x, y, z] : v)

const int mod = 1e9+7;

int main(){
 cin.tie(0)->sync_with_stdio(false);
 int t; cin >> t; while (t--) {
  int n, m; cin >> n >> m;
  bool found = false;
  int p = 1;
  rep(i, 1, n, 1) rep(j, 1, m, 1) {
   char c; cin >> c; if (c == '0') found = true;
   else (p *= 2) %= mod;
  }
  cout << (found ? p : p-1) << '\n'; 
 }
}