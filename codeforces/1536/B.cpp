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

int main(){
 cin.tie(0)->sync_with_stdio(false);
 vec<str> v;
 auto rec = [&](const auto& self, int l, int n, str res) -> void {
  if (l == n) v.pb(res);
  else {
   rep(i, 0, 25, 1) self(self, l+1, n, res+char('a'+i));
  }
 };
 rep(i, 1, 3, 1) rec(rec, 0, i, "");
 int t; cin >> t; while (t--) {
  int n; cin >> n; str s; cin >> s;
  each(x, v) {
   if (s.find(x) == str::npos) {
    cout << x << '\n'; break;
   }
  }
 }
}