#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
const int LIM=2e5+7;
map<string,int>days;
set<pair<int,int>>H;
bool works[LIM][7];
int holidays[LIM], nxt[LIM][1<<7], worked[LIM], ans[LIM], wrzucone[LIM], day;
vector<int>projects[LIM];
priority_queue<pair<int,int>>q;
priority_queue<int>Q[LIM];
int give_next(int x) {
  worked[x]=max(worked[x], day);
  while(!works[x][worked[x]%7]) ++worked[x];
  auto it=H.lower_bound({worked[x], 0});
  if(it!=H.end()) {
    auto p=*it;
    if(p.st==worked[x]) {
      int mask=0;
      rep(i, 7) if(works[x][i]) mask+=1<<i;
      worked[x]=nxt[p.nd][mask];
      return worked[x];
    }
  }
  return worked[x];
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  days["Monday"]=0;
  days["Tuesday"]=1;
  days["Wednesday"]=2;
  days["Thursday"]=3;
  days["Friday"]=4;
  days["Saturday"]=5;
  days["Sunday"]=6;
  int n, m, k;
  cin >> n >> m >> k;
  rep(i, n) {
    int p;
    cin >> p;
    while(p--) {
      string s;
      cin >> s;
      works[i][days[s]]=1;
    }
  }
  rep(i, m) {
    cin >> holidays[i]; --holidays[i];
    H.insert({holidays[i], i});
  }
  rep(i, 1<<7) if(i) {
    for(int j=m-1; j>=0; --j) {
      nxt[j][i]=holidays[j]+1;
      while(!(i&(1<<(nxt[j][i]%7)))) ++nxt[j][i];
      int l=j+1;
      while(l<m && holidays[l]<nxt[j][i]) ++l;
      if(l<m && holidays[l]==nxt[j][i]) nxt[j][i]=nxt[l][i];
    }
  }
  rep(i, k) {
    int p;
    cin >> p;
    while(p--) {
      int a;
      cin >> a; --a;
      projects[i].pb(a);
    }
    reverse(all(projects[i]));
    Q[projects[i].back()].push(-i);
  }
  rep(i, n) if(!Q[i].empty()) {
    q.push({-give_next(i), i});
    wrzucone[i]=1;
  }
  while(!q.empty()) {
    int o=-q.top().st, x=q.top().nd; q.pop();
    vector<int>ktore, jakie, sprawdz;
    ktore.pb(x);
    while(!q.empty() && -q.top().st==o) {
      ktore.pb(q.top().nd);
      q.pop();
    }
    sprawdz=ktore;
    day=max(day, o+1);
    for(auto x : ktore) {
      jakie.pb(-Q[x].top());
      Q[x].pop();
      wrzucone[x]=0;
    }
    rep(i, ktore.size()) {
      projects[jakie[i]].pop_back();
      if(!projects[jakie[i]].size()) {
        ans[jakie[i]]=o;
        continue;
      }
      Q[projects[jakie[i]].back()].push(-jakie[i]);
      sprawdz.pb(projects[jakie[i]].back());
    }
    for(auto i : sprawdz) if(!wrzucone[i] && !Q[i].empty()) {
      q.push({-give_next(i), i});
      wrzucone[i]=1;
    }
  }
  rep(i, k) cout << ans[i]+1 << " ";
  cout << '\n';
}
