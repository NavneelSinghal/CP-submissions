#include<bits/stdc++.h>
using namespace std;
    
    string a, b;
    vector<long long int> pr;
    
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>a>>b;
    long long int n = a.size();
    long long int k = b.size();
    long long int sum = 0;
    for(long long int i=0; i<k; i++){
        sum += b[i]-'0';
        pr.push_back(sum);
    }
    long long int ans = abs(pr[k-n] - (k-n+1)*(a[0]-'0'));
    for(long long int i=1; i<n; i++){
        ans+=abs((pr[k-n+i]-pr[i-1]) - (k-n+1)*(a[i]-'0'));
    }
    cout<<ans;
}
