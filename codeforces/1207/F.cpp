#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n = 500000;
        vector<int> a(n + 1);
        int q;
        cin >> q;
        int threshold = 700;
        vector b(threshold + 1, vector<int>(threshold));
        // b[i][j] = sum of stuff at indices j mod i with i <= threshold
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int x, y;
                cin >> x >> y;
                a[x] += y;
                for (int j = 1; j <= threshold; ++j) b[j][x % j] += y;
            } else {
                int x, y;
                cin >> x >> y;
                if (x <= threshold) {
                    cout << b[x][y] << '\n';
                } else {
                    int ans = 0;
                    if (y == 0) y = x;
                    for (int i = y; i <= n; i += x) ans += a[i];
                    cout << ans << '\n';
                }
            }
        }
    }
}
