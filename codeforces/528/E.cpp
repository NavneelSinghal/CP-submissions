#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
typedef long double ld;
#define double ld
typedef pair<double, double> pd;
#define MAX 3010
#define F first
#define S second
#define mp make_pair
using namespace std;

int a[MAX], b[MAX], c[MAX], rnk[MAX];

bool comp(int &x, int &y){
  return ((double)atan2(b[x], -a[x])) > ((double)atan2(b[y], -a[y]));
}

pd intersect(int u, int v){
  double d=a[u]*b[v]-a[v]*b[u];
	return make_pair((double)(b[v]*c[u]-b[u]*c[v])/d,(double)(a[u]*c[v]-a[v]*c[u])/d);
}

signed main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout<<fixed<<setprecision(11);
  int n;
  cin>>n;

  for(int i = 0; i<n; i++){
    cin>>a[i]>>b[i]>>c[i];
    if(a[i]<0){
      a[i]*=-1;
      b[i]*=-1;
      c[i]*=-1;
    }
    rnk[i] = i;
  }

  sort(rnk, rnk+n, comp);
  double ans = 0.0;

  for(int i = 0; i<n; i++){
    int l = rnk[i];
    pd sum = mp(0.0, 0.0);
    for(int j = 1; j<n; j++){
      int m = rnk[(i+j)%n];
      pd point = intersect(l, m);
      ans += (double) 3.0/n/(n-1)/(n-2)*(sum.F*point.S - sum.S*point.F);
      sum.F += point.F;
      sum.S += point.S;
    }
  }

  cout<<fabs(ans);
}
