#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
const ll INF=1e18+7;
void solve() {
  ll n;
  cin >> n;
  pair<ll,ll>ans={INF, INF};
  for(ll i=1; i*i<=n; ++i) {
    if(n%i==0) {
      ans=min(ans, {max(n-i, i), min(n-i, i)});
      ans=min(ans, {max(n-n/i, n/i), min(n-n/i, n/i)});
    }
  }
  cout << ans.st << " " << ans.nd << '\n';
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int _;
  cin >> _;
  while(_--) solve();
}