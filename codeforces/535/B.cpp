#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
int pow10(int n){
  int ans = 1;
  while(n){
    n/=10;
    ans*=10;
  }
  return ans;
}
int p10(int n){
  int ans = 0;
  while(n){
    n/=10;
    ans+=1;
  }
  return ans;;
}
signed main(){
  int n;
  cin>>n;
  int p = p10(n);
  int p1 = pow10(n);
  p1 = p1*7;
  n += p1;
  int ans = 0;
  for(int i = 0; i<=p; i++){
    if(n%10 == 7){
      ans += (1<<i);
    }
    n/=10;
  }
  cout<<ans-1;
  return 0;
}