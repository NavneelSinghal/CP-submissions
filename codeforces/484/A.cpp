#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
int dig(int a){
  int ans = 0; 
  while(a){
    ans++;
    a>>=2;
  }
  return ans;
}

void solve(){
  int a, b;
  cin>>a>>b;
  if(a>b){
    swap(a, b);
  }
  int i;
  for(i = 60; i>=0; i--){
    if((a&(1ll<<i)) != (b&(1ll<<i))){
      break;
    }
  }
  int ans = (a>>(i+1))<<(i+1);
  a = a-ans;
  b = b-ans;
  //i+1 is no. of digits in b
  if(b==(1ll<<(i+1))-1){
    cout<<b+ans<<"\n";
  }
  else{
    cout<<(1ll<<(i))-1+ans<<"\n";
  }

}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}