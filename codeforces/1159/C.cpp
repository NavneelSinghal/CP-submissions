#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int n, m;
  cin>>n>>m;
  int sumb = 0; int sumg = 0;
  vector<int> b(n), g(m);
  for(int i = 0; i<n; i++){
    cin>>b[i];
    sumb+=b[i];
  }
  for(int i = 0; i<m; i++){
    cin>>g[i];
    sumg+=g[i];
  }
  sort(b.begin(), b.end());
  sort(g.begin(), g.end());
  if(b[n-1]>g[0]){
    cout<<-1;
    return 0;
  }
  else if(b[n-1]==g[0]){
    cout<<sumb*m + sumg - m*b[n-1];
    return 0;
  }
  else{
    cout<<sumb*m + sumg - (m-1)*b[n-1] - b[n-2];
    return 0;
  }
  
  
}
