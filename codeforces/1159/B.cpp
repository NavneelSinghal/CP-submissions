#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int n;
  cin>>n;
  int ans = 1e18;
  for(int i=0; i<n; i++){
    int x;
    cin>>x;
    ans=min(ans, x/max(i, n-i-1));
  }
  cout<<ans;
}
