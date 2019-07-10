#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int n;
  cin>>n;
  string a;
  cin>>a;
  int mn = 0;
  int x = 0;
  for(int i = 0; i<n; i++){
    if(a[i] == '-'){
      x--;
    }
    else x++;
    mn=min(x, mn);
  }
  mn = -mn;
  //mn is number of stones initially
  for(int i = 0; i<n; i++){
    if(a[i] == '-'){
      mn--;
    }
    else mn++;
  }
  cout<<mn;

}
