#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    cout << 3*n + 4 << endl;
    cout << "0 0\n";
    for(int i = 0; i <= n; i++){
        cout << i << " " << i + 1 << endl;
        cout << i + 1 << " " << i << endl;
        cout << i + 1 << " " << i + 1 << endl;
    }
    return 0;
}