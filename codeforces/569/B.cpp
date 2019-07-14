#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(1e5+5);
    vector<int> mark(1e5+5);
    vector<int> used(1e5+5);
    for(int i = 0; i<n; i++){
        cin>>a[i];
        a[i]--;
        if(!mark[a[i]] && a[i]<n && a[i]>=0){
            mark[a[i]] = 1;
        }
    }
    vector<int> unmarked;
    for(int i = 0; i<n; i++){
        if(!mark[i]){
            unmarked.push_back(i);
        }
    }
    int j = 0;
    for(int i = 0; i<n; i++){
        if(!mark[a[i]] || used[a[i]]){
            cout<<unmarked[j]+1<<" ";
            used[unmarked[j]]=1;
            j++;
        }
        else{
            cout<<a[i]+1<<" ";
            used[a[i]]=1;
        }
    }
}