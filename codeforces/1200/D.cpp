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
        int n, k;
        cin >> n >> k;
        vector ok(2, vector(n - k + 1, vector(n - k + 1, 0)));
        vector<string> a(n);
        for (auto& x : a) cin >> x;
        int already_white = 0;
        for (int iter = 0; iter < 2; ++iter) {
            if (iter)
                for (int i = 0; i < n; ++i)
                    for (int j = 0; j < i; ++j) swap(a[i][j], a[j][i]);
            auto& cleared = ok[iter];
            vector<array<int, 4>> rectangles;
            for (int i = 0; i < n; ++i) {
                int first_black = -1, last_black = -1;
                for (int j = 0; j < n; ++j) {
                    if (a[i][j] == 'B') {
                        last_black = j;
                        if (first_black == -1) first_black = j;
                    }
                }
                if (first_black == -1) {
                    already_white++;
                } else if (last_black - first_black < k) {
                    rectangles.emplace_back(
                        array{max(0, i - k + 1), max(0, last_black - k + 1),
                              min(i, n - k) + 1, min(n - k, first_black) + 1});
                }
            }
            vector matrix(n - k + 2, vector<int>(n - k + 2));
            for (auto [i1, j1, i2, j2] : rectangles) {
                if (i1 < i2 && j1 < j2) {
                    matrix[i1][j1] += 1;
                    matrix[i1][j2] += -1;
                    matrix[i2][j1] += -1;
                    matrix[i2][j2] += 1;
                }
            }
            for (int i = 0; i + k <= n; ++i) {
                int sum = 0;
                for (int j = 0; j + k <= n; ++j) {
                    sum += matrix[i][j];
                    cleared[i][j] = sum;
                    if (i > 0) cleared[i][j] += cleared[i - 1][j];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i + k <= n; ++i)
            for (int j = 0; j + k <= n; ++j)
                ans = max(ans, ok[0][i][j] + ok[1][j][i]);
        ans += already_white;
        cout << ans << '\n';
    }
}
