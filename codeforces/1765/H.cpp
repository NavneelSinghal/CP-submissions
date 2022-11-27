#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
const int LIM=2e3+7;
vector<int>V[LIM];
int T[LIM][LIM];
pair<int,int>P[LIM];
void DFS(int x, int k) {
  T[k][x]=1;
  for(auto i : V[x]) if(!T[k][i]) DFS(i, k);
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  rep(i, n) {
    cin >> P[i].st; --P[i].st;
    P[i].nd=i;
  }
  rep(i, m) {
    int a, b;
    cin >> a >> b; --a; --b;
    V[a].pb(b);
  }
  rep(i, n) rep(j, n) for(auto l : V[j]) P[j].st=min(P[j].st, P[l].st-1);
  rep(i, n) DFS(i, i);
  sort(P, P+n);
  rep(i, n) {
    set<int>S;
    rep(j, n) S.insert(j);
    rep(j, n) {
      if(T[P[j].nd][i]) {
        auto it=S.begin();
        int a=*it;
        if(P[j].nd==i) cout << a+1 << " ";
        S.erase(it);
      } else {
        auto it=S.upper_bound(P[j].st); --it;
        S.erase(it);
      }
    }
  }
  cout << '\n';
}