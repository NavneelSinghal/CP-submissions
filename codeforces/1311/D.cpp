#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--){
        int a, b, c;
        cin >> a >> b >> c;
        int outa = -1, outb = -1, outc = -1;
        int best = 1e9;
        for(int x = 1; x <= 2*a; x++){
            for(int y = x; y <= 2*b; y += x){
                for(int i = 0; i < 2; i++){
                    int z = y*(c/y) + i*y;
                    int cur = abs(x - a) + abs(y - b) + abs(z - c);
                    if(z >= y && cur < best){
                        best = cur;
                        outa = x;
                        outb = y;
                        outc = z;
                    }
                }
            }
        }
        cout << best << "\n";
        cout << outa << " " << outb << " " << outc << "\n";
    }
}

