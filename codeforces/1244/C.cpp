#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, p, w, d;
    cin >> n >> p >> w >> d;
    int x, y = -1, z;
    for(int i = 0; i < w; i++){
        if((p - i*d) % w == 0){
            y = i;
            break;
        }
    }
    if(y == -1){
        cout << -1 << endl;
        return 0;
    }
    x = (p - y * d) / w;
    z = n - x - y;
    if(x >= 0 && y >= 0 && z >= 0){
        cout << x << " " << y << " " << z << "\n";
        return 0;
    }
    else{
        cout << -1 << endl;
        return 0;
    }
}

