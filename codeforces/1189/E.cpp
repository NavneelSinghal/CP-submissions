#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int n, p, k;
  cin>>n>>p>>k;
  map<int, int> m;
  int ans = 0;
  for(int i = 0; i<n; i++){
    int x;
    cin>>x;
    x = ((((x*x)%p)*((x*x)%p))%p - (k*x)%p + p)%p;
    ans += m[x];
    m[x]++;
  }
  cout<<ans;
  return 0;

}
