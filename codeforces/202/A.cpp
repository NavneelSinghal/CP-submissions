#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
bool ispal(string s){
  bool ans = true;
  for(int i = 0; i<s.size(); i++){
    ans = ans && (s[i] == s[s.size()-1-i]);
  }
  return ans;
}
signed main(){
  string s;
  cin>>s;
  int n = s.size();
  string ans = "";
  for(int i = 0; i<(1<<n); i++){
    string x;
    for(int j = 0; j<n; j++){
      if((1<<j) & i){
        x = x + s[j];
      }
    }
    if(ispal(x)){
      if(!lexicographical_compare(x.begin(), x.end(), ans.begin(), ans.end())){
        ans = x;
      }
    }
  }
  cout<<ans;
  return 0;
}