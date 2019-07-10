#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int cnt1, cnt2, cnt3, cnt4;
  cin>>cnt1>>cnt2>>cnt3>>cnt4;
  if(cnt1!=cnt4){
    cout<<0;
    return 0;
  }  
  if(cnt3>=1){
    if(cnt1>=1){
      cout<<1;
      return 0;
    }
    cout<<0;
    return 0;
  }
  cout<<1;
  return 0;
}
