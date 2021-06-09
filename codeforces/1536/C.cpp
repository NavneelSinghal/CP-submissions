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

int main(){
 cin.tie(0)->sync_with_stdio(false);
 int t; cin >> t; while (t--) {
  int n; cin >> n;
  map<pair<int, int>, int> m;
  int x = 0, y = 0;
  rep(i, 0, n-1, 1) {
    char c; cin >> c;
    x += (c == 'D'); y++;
    int g = __gcd(x, y);
    cout << ++m[{x/g, y/g}] << ' ';
  }
  cout << "\n";
 }
}