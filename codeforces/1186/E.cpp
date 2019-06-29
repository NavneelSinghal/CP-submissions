#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define M 2000
#define N 2000
int n, m;
char a[2000][2000];
int aux[2000][2000];
void preProcess(){
   for (int i=0; i<N; i++) 
      aux[0][i] = (a[0][i]-'0'); 
  
   for (int i=1; i<M; i++) 
      for (int j=0; j<N; j++) 
         aux[i][j] = (a[i][j]-'0') + aux[i-1][j]; 
  
   for (int i=0; i<M; i++) 
      for (int j=1; j<N; j++) 
         aux[i][j] += aux[i][j-1]; 
} 
bool g(int x, int y){
    int ax = 0, ay = 0;
    while(x > 0){
        ax += x%2;
        x /= 2;
    }
    while(y > 0){
        ay += y%2;
        y /= 2;
    }
    return bool((ax+ay+1)%2);
}

int f(int x, int y){
    x--;
    y--;
    int ans = 0;
    
    if(x<0 || y<0){
        return 0;
    }
    
    ans = (x/(2*n))*(y/(2*m))*aux[2*n-1][2*m-1] + (y/(2*m))*aux[x%(2*n)][2*m-1] + (x/(2*n))*aux[2*n-1][y%(2*m)];
    ans += g(x/(2*n), y/(2*m)) ? aux[(x)%(2*n)][(y)%(2*m)] : ((x%(2*n)+1)*(y%(2*m)+1) - aux[x%(2*n)][y%(2*m)]);
    
    
    return ans;
}
signed main(){
    int q;
    cin>>n>>m>>q;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin>>a[i][j];
            a[i][j+m] = a[i][j]=='0' ? '1':'0';
            a[i+n][j+m] = a[i][j];
            a[i+n][j] = a[i][j]=='0' ? '1':'0';
        }
    }
    preProcess();
    for(int i = 0; i<q; i++){
        int x1, x2, y1, y2;
        cin>>x1>>y1>>x2>>y2;
        x1--;
        y1--;
        int ans = f(x2, y2) - f(x1, y2) - f(x2, y1) + f(x1, y1);
        cout<<ans<<"\n";
    }
    return 0;
}