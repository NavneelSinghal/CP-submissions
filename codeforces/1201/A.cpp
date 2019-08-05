#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin>>n>>m;
    char a[n][m];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin>>a[i][j];
        }
    }
    int b[m][5];
    for(int k = 0; k<m; k++)
    for(int j = 0; j<5; j++){
        b[k][j] = 0;
        for(int i = 0; i<n; i++){
            if(a[i][k] == 'A'+j){
                b[k][j]++;
            }
        }
    }
    int c[m];
    for(int i = 0; i<m; i++){
        cin>>c[i];
    }
    int ans = 0;
    for(int i = 0; i<m; i++){
        int mult = 0;
        for(int j = 0; j<5; j++){
            mult = max(mult, b[i][j]);
        }
        ans += mult*c[i];
    }
    cout<<ans<<endl;
    
}