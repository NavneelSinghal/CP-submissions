#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i = 0; i<n; i++){
    cin>>a[i];
  }
  vector<int> prefix(n+1);
  for(int i = 1; i<=n; i++){
    prefix[i] = prefix[i-1]+a[i-1];
  }
  int q;
  cin>>q;
  for(int i = 0; i<q; i++){
    int l, r;
    cin>>l>>r;
    cout<<(prefix[r] - prefix[l-1])/10<<endl;
  }
}
