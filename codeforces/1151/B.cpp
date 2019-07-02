#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll

signed main(){
  int n, m;
  cin>>n>>m;
  int a[n][m];
  for(int i = 0; i<n; i++){
    for(int j = 0; j<m; j++){
      cin>>a[i][j];
    }
  }
  int x = 0;
  for(int i = 0; i<n; i++){
    x = x^a[i][0];
  }
  if(x != 0){
    cout<<"TAK\n";
    for(int i = 0; i<n; i++){
      cout<<"1 ";
    }
  }
  else{
  int idx = -1;
  int idy = -1;
    for(int i = 0; i<n; i++){
      for(int j = 1; j<m; j++){
        if(a[i][j]!=a[i][0]){
          idx = i;
          idy = j;
        }
      }
    }
    if(idx==-1){
      cout<<"NIE\n";
    }
    else{
      cout<<"TAK\n";
      for(int i = 0; i<n; i++){
        if(i==idx){
          cout<<idy+1<<" ";
        }
        else cout<<"1 ";
      }
    }
  }

}