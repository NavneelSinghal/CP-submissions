#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin>>n;
  vector<int> deg(n);
  for(int i = 0; i<n-1; i++){
    int x, y;
    cin>>x>>y;
    x--; y--;
    deg[x]++;
    deg[y]++;
  }
  for(int i = 0; i<n; i++){
    if(deg[i]==2){
      cout<<"NO";
      return 0;
    }
  }
  cout<<"YES";
  return 0;
}
