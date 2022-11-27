#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll n, m;
  cin >> n >> m;
  multiset<ll>S;
  ll ans=0;
  rep(i, n) {
    ll a;
    cin >> a;
    ans+=a;
    S.insert(a);
  }
  while(!S.empty()) {
    ++ans;
    auto it=S.end(); --it;
    ll x=*it;
    S.erase(it);
    while(true) {
      auto it2=S.upper_bound(m-x);
      if(it2==S.begin()) break;
      --it2;
      x=*it2;
      S.erase(it2);
    }
  }
  cout << ans << '\n';
}