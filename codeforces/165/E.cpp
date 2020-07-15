#include <bits/stdc++.h>
using namespace std;

const int m = 22;
const int M = 1 << m;

unsigned dp[M], a[1 << (m - 2)];

int main () {
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   
    memset(dp, UINT_MAX, sizeof dp);
    int n, x; 
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> x;
        dp[x] = x;
        a[i] = x;
    }
    
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < M; ++mask) {
            if (~dp[mask]) {
                dp[mask | (1 << i)] = dp[mask];
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cout << (int) dp[(~a[i]) & (M - 1)] << " ";
    }
    
    cout << endl;

}
