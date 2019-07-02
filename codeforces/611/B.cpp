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

int f(int n, int i){
  int ans = (1ll<<(n))-1;
  ans &= ~(1ll<<i);
  return ans;
}

signed main(){
  int a, b;
  cin>>a>>b;
  int c = dig(a), d = dig(b);
  
  int ans = 0;
  for(int i = c+1; i<d; i++){
    ans += (i-1);
  }
  for(int i = 0; i<(c-1); i++){
    int r = f(c, i); //f(c, i) is integer with ones at all c positions except ith bit from right which is 0
    if(a<=r && r<=b){
      ans++;
      //cout<<r<<" ";
    }
  }
  if(c!=d)
  for(int i = 0; i<(d-1); i++){
    int r = f(d, i);
    if(a<=r && r<=b){
      ans++;
      //cout<<r<<" ";
    }
  }
  cout<<ans;
}