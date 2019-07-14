#include<bits/stdc++.h>
using namespace std;
#define MAX 1e9
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    map<int, int> m;
    pair<int, int> p = {0,0};
    map<int, int> first_loc;
    map<int, int> last_loc;
    for(int i = 0; i<n; i++){
        cin>>a[i];
        m[a[i]]++;
        
        first_loc[a[i]] = -1;
        
        last_loc[a[i]] = i;
    }
    for(int i = 0; i<n; i++){
        if(first_loc[a[i]]==-1) first_loc[a[i]] = i;
    }
    for(auto x : m){
        if(x.second > p.second){
            p = x;
        }
    }
    vector<pair<int, int> > v;
    for(auto x : m){
        if(x.second == p.second){
            v.push_back(x);
        }
    }
    int diff = n;
    int l, r;
    for(auto w : v){
        int left = first_loc[w.first];
        int right = last_loc[w.first];
        int diff2 = right - left;
        if(diff2 < diff){
            l = left, r = right;
            diff = diff2;
        }
    }
    cout<<l+1<<" "<<r+1;
    return 0;
}
