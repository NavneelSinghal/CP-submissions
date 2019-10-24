#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
#define int ll
signed main() {
    int n, m;
    cin>>n>>m;
    vector<int> fib(max(n, m)+2);
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i<= max(n, m)+1; i++){
        fib[i] = fib[i-1]+fib[i-2];
        fib[i]%=MOD;
    }
    cout<<(2*(fib[n+1]+fib[m+1]-1))%MOD<<endl;
}