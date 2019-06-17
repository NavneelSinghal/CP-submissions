#include<bits/stdc++.h>
using namespace std;
int main(){
    int k;
    cin>>k;
    vector<int> a(12);
    for(int i = 0; i<12; i++){
        cin>>a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int j = 0;
    int sum  = 0;
    while(sum<k && j<12){
        sum += a[j];
        j++;
    }
    if(sum < k){
        cout<<-1;
    }
    else{
        cout<<j;
    }
}