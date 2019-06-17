#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int k;
    cin>>k;
    vector<int> a(k), b(n*k, 1), c(n*k);
    for(int i = 0; i<k; i++){
        cin>>a[i];
        a[i]--;
    }
    for(int i = 0; i<k; i++){
        b[a[i]] = 0;
        c[i*n] = a[i];
    }
    int j = 0;
    for(int i = 0; i<k; i++){
        int count = 0;
        while(count<n-1){
            
            while(b[j]==0){
                j++;
            }
            c[i*n+count+1] = j;
            count++;
            j++;
        }
    }
    for(int i = 0; i<k; i++){
        for(int l = 0; l<n; l++){
        c[i*n+l]++;
        cout<<c[i*n+l]<<" ";}
        cout<<endl;
    }
}