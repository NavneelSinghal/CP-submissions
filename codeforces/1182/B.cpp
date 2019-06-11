#include<bits/stdc++.h>
using namespace std;
int main(){
    int h, w;
    cin>>h>>w;
    char a[h+2][w+2];
    if(h<=2 || w<=2){
        cout<<"NO";
        return 0;
    }
    for(int i = 1; i<=h; i++){
        for(int j=1; j<=w; j++){
            a[i][j]='.';
        }
    }
    int tot = 0;
    for(int i = 1; i<=h; i++){
        for(int j=1; j<=w; j++){
            cin>>a[i][j];
            if(a[i][j]=='*') tot++;
        }
    }
    int ans = 0;
    for(int i = 1; i<=h; i++){
        for(int j=1; j<=w; j++){
            if(a[i][j-1]=='*' && a[i][j+1]=='*' && a[i-1][j]=='*' && a[i+1][j]=='*' && a[i][j]=='*'){
                ans++;
            }
        }
    }
    if(ans!=1){
        cout<<"NO";
        return 0;
    }
    int x, y;
    for(int i = 1; i<=h; i++){
        for(int j=1; j<=w; j++){
            if(a[i][j-1]=='*' && a[i][j+1]=='*' && a[i-1][j]=='*' && a[i+1][j]=='*' && a[i][j]=='*'){
                x = i;
                y = j;
                break;
            }
        }
    }
    ans = 1;
    for(int i = x+1; a[i][y]=='*'; i++){
        ans++;
    }
    for(int i = x-1; a[i][y]=='*'; i--){
        ans++;
    }
    for(int j = y+1; a[x][j]=='*'; j++){
        ans++;
    }
    for(int j = y-1; a[x][j]=='*'; j--){
        ans++;
    }
    if(ans==tot){
        cout<<"YES";
    }
    else{
        cout<<"NO";
    }
    
}