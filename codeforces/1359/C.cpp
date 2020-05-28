#include <bits/stdc++.h>
using namespace std;

#define int long long

#define INF 1e9

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int q;
    cin >> q;
    while(q--){
        int h, c, t;
        cin >> h >> c >> t;
        if(t <= (h + c)/2){
            cout << 2 << '\n';
        }
        else{
            int left = 1;
            int right = INF;
            int ans = 0;
            while(left <= right){
                int mid = (left + right)/2;
                if((mid+1)*h + mid*c >= (2*mid + 1)*t){
                    left = mid + 1;
                    ans = mid;
                }
                else{
                    right = mid - 1;
                }
            }
            double x = ans;
            double t1 = ((x + 1) * h + x * c) / (2 * x + 1);
            double t2 = ((x + 2) * h + (x + 1) * c) / (2 * x + 3);
            if(abs(t1 - t) <= abs(t - t2)){
                cout << 2 * ans + 1 << endl;
            }
            else{
                cout << 2 * ans + 3 << endl;
            }
        }
    }
}
