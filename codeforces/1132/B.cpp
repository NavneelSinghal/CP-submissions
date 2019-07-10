#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed   main(){
  int n;
  cin>>n;
  vector<int> a(n);
  int sum = 0;
  for(int i = 0; i<n; i++){
    cin>>a[i];
    sum += a[i];
  }
  sort(a.rbegin(), a.rend());
  int m;
  cin>>m;
  for(int i = 0; i<m; i++){
    int q;
    cin>>q;
    cout<<sum - a[q-1]<<endl;
  }
}
