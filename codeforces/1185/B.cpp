#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin>>n;
    while(n--){
        string a, b;
        cin>>a>>b;
        int as = a.size();
        int bs = b.size();
        int ct = 1;
        int i = 0, j = 0;
        while(i<as && j<bs){
            if(a[i]!=b[j]){
                cout<<"NO\n";
                ct = 0;
                break;
            }
            else{
                int x = 0;
                int y = 0;
                while(a[i]==b[j]){
                    i++;
                    x++;
                }
                while(b[j]==a[i-1]){
                    j++;
                    y++;
                }
                if(x>y){
                    cout<<"NO\n";
                ct = 0;
                break;
                }
            }
        }
        if(ct &&  i == as && j == bs){
            cout<<"YES\n";
        }
        else if(ct){
            cout<<"NO\n";
        }
    }
}