#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
int dig(int a){
  int ans = 0;
  while(a){
    ans++;
    a>>=1;
  }
  return ans;
}


signed main(){
  int x;
  cin>>x;
  vector<int> v;
  int ans = 0;
  while(! (__builtin_popcount(x+1) == 1)){
    ans+=1;
    if(ans%2==0){
      x+=1;
      continue;
    }
    int r = dig(x) - 1;
    if((1ll<<r)!=x) r++;
    x = ((1ll<<(r))-1)^x;
    v.push_back(r);
  }
  cout<<ans<<endl;
  for(int i = 0; i<v.size(); i++){
    cout<<v[i]<<" ";
  }
}