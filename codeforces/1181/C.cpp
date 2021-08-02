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
        int n, m;
        cin >> n >> m;
        vector s(n, string());
        for (auto &x : s) cin >> x;
        vector below(n, vector<int>(m));
        auto right = below;
        for (int j = 0; j < m; ++j) {
            below[n - 1][j] = 1;
            for (int i = n - 2; i >= 0; --i) {
                below[i][j] = (s[i][j] == s[i + 1][j]) ? below[i + 1][j] + 1 : 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            right[i][m - 1] = 1;
            for (int j = m - 2; j >= 0; --j) {
                right[i][j] = (s[i][j] == s[i][j + 1]) ? right[i][j + 1] + 1 : 1;
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int height = below[i][j];
                if (i + 3 * height > n) continue;
                if (below[i + height][j] != height) continue;
                if (below[i + 2 * height][j] < height) continue;
                int max_length = m;
                for (int k = 0; k < 3 * height; ++k) {
                    max_length = min(max_length, right[i + k][j]);
                }
                ans += max_length;
            }
        }
        cout << ans << '\n';
    }
}
