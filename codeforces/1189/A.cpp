#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin>>n;
  string s;
  cin>>s;
  int a, b;
  a=0; b=0;
  for(int i = 0; i<n; i++){
    if(s[i] == '0'){
      a++;
    }
    else{
      b++;
    }
  }
  if(b!=a){
    cout<<1<<endl;
    cout<<s;
  }
  else{
    cout<<2<<endl;
    cout<<s[0]<<" ";
    for(int i = 1; i<n; i++){
      cout<<s[i];
    }
  }
}
