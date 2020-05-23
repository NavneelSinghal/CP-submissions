#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        bool found = false;
        string a;
        string b;
        for(auto c : s){
            if(c == '0' && !found){
                a += '0';
                b += '0';
            }
            else if(c == '2' && !found){
                a += '1';
                b += '1';
            }
            else if(c == '0' && found){
                a += '0';
                b += '0';
            }
            else if(c == '2' && found){
                a += '0';
                b += '2';
            }
            else if(c == '1' && found){
                a += '0';
                b += '1';
            }
            else if(c == '1' && !found){
                a += '1';
                b += '0';
                found = true;
            }
        }
        cout << a << "\n" << b << "\n";
    }
}
