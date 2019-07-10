#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i = 0; i<n; i++){
    cin>>a[i];
  }
  sort(a.begin(), a.end());
  if(a[n-1]>=a[n-2]+a[n-3]){
    cout<<"NO";
    return 0;
  }
  cout<<"YES\n";
  for(int i = 0; 2*i<n; i++){
    cout<<a[2*i]<<" ";
  }
  vector<int> v;
  for(int i = 0; 2*i+1<n; i++){
    v.push_back(a[2*i+1]);
  }
  for(auto it = v.end()-1; it>=v.begin(); it--){
    cout<<*it<<" ";
  }
}
