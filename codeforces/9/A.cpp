#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main() {
    int a, b;
    cin>>a>>b;
    int h = max(a, b);
    int num = 6 - h + 1;
    int g = __gcd(num, 6ll);
    cout<<num/g<<'/'<<6/g<<endl;
}