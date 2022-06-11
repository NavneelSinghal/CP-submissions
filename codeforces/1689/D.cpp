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
using ull = uint64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for (auto& x : a) cin >> x;
        constexpr int inf = 1e9;
        pair<int, int> top{inf, inf}, bottom{-inf, inf}, left{inf, inf},
            right{inf, -inf};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == 'B') {
                    int x = i + j;
                    int y = i - j;
                    if (top.first > x) top = {x, y};
                    if (bottom.first < x) bottom = {x, y};
                    if (left.second > y) left = {x, y};
                    if (right.second < y) right = {x, y};
                }
            }
        }
        pair<int, int> ans{-1, -1};
        int mn = inf;
        auto dist = [](auto p1, auto p2) {
            return max(abs(p1.first - p2.first), abs(p1.second - p2.second));
        };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pair<int, int> p{i + j, i - j};
                int mx_dist = max({dist(p, top), dist(p, bottom), dist(p, left),
                                   dist(p, right)});
                if (mx_dist < mn) {
                    mn = mx_dist;
                    ans = {i + 1, j + 1};
                }
            }
        }
        assert(ans.first != -1);
        cout << ans.first << ' ' << ans.second << '\n';
    }
}