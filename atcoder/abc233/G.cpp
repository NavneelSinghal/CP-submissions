#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        // dp[i1][j1][i2][j2] = ans for subarray [i1, i2] * [j1, j2]
        int n;
        cin >> n;
        vector<string> s(n);
        for (auto& x : s) cin >> x;
        vector dp(n, vector(n, vector(n, vector(n, 100))));

        auto solve = [&](const auto& self, int i1, int j1, int i2,
                         int j2) -> int {
            if (i1 > i2 || j1 > j2) return 0;
            if (dp[i1][j1][i2][j2] != 100) return dp[i1][j1][i2][j2];
            if (i1 == i2 && j1 == j2) dp[i1][j1][i2][j2] = s[i1][j1] == '#';

            int n1 = i2 - i1 + 1;
            int m1 = j2 - j1 + 1;
            int ans = max(n1, m1);
            for (int i = i1; i <= i2; ++i) {
                bool check = true;
                for (int j = j1; j <= j2; ++j) {
                    if (s[i][j] == '#') {
                        check = false;
                        break;
                    }
                }
                if (check)
                    ans = min(ans, self(self, i1, j1, i - 1, j2) +
                                       self(self, i + 1, j1, i2, j2));
            }
            for (int j = j1; j <= j2; ++j) {
                bool check = true;
                for (int i = i1; i <= i2; ++i) {
                    if (s[i][j] == '#') {
                        check = false;
                        break;
                    }
                }
                if (check)
                    ans = min(ans, self(self, i1, j1, i2, j - 1) +
                                       self(self, i1, j + 1, i2, j2));
            }
            return dp[i1][j1][i2][j2] = ans;
        };

        int ans = solve(solve, 0, 0, n - 1, n - 1);
        cout << ans << '\n';
    }
}
