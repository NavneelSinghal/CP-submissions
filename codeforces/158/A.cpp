#include<bits/stdc++.h>
using namespace std;

typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

int main(){
    int n, k;
    cin>>n>>k;
    vi a;
    int ax = n;
    while(ax--)
    {
        int x;
        cin>>x;
            a.push_back(x);
    }
    int i = 0;
    while(i<n && a[i]>0 && a[i]>=a[k-1]){
        i+=1;
    }
    cout<<i;
    
    return 0;
}