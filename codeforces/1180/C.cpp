#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main(){
    int n, q;
    cin>>n>>q;
    vector<int> a(n);
    vector<int> fi, se;
    deque<int> d;
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }
    for(int i = 0; i<n; i++){
        d.push_back(a[i]);
    }
    fi.push_back(a[0]);
    se.push_back(a[1]);
    for(int i = 0; i<n; i++){
        int A = d.front();
        d.pop_front();
        int B = d.front();
        d.pop_front();
        fi.push_back(A);
        se.push_back(B);
        if(B>=A){
            swap(A, B);
        }
        d.push_front(A);
        d.push_back(B);
    }
    vector<int> b(n);
    for(int i = 0; i<n; i++){
        b[i] = d.front();
        d.pop_front();
    }
    for(int j = 0; j<q; j++){
        int x;
        cin>>x;
        if(x<n){
            cout<<fi[x]<<" "<<se[x]<<endl;
        }
        else{
            cout<<b[0]<<" "<<b[1+(x-2)%(n-1)]<<endl;
        }
    }
    
}