#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<ll> a(n);
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    vector<ll> cost(5), num(5);
    for(int i = 0; i<5; i++){
        cin>>cost[i];
    }
    ll rem = 0;
    for(int i = 0; i<n; i++){
        rem+=a[i];
        num[4] += rem/cost[4], rem=(rem%cost[4]);
        num[3] += rem/cost[3], rem=(rem%cost[3]);
        num[2] += rem/cost[2], rem=(rem%cost[2]);
        num[1] += rem/cost[1], rem=(rem%cost[1]);
        num[0] += rem/cost[0], rem=(rem%cost[0]);
    }
    for(int i = 0; i<5; i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
    cout<<rem;
    return 0;
}