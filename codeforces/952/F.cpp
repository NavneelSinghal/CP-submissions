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
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string s;
        cin >> s;
        int ans = 0;
        int cur = 0;
        int sign = 1;
        for (auto c : s) {
            if (c == '+') {
                ans += sign * cur;
                sign = 1;
                cur = 0;
            } else if (c == '-') {
                ans += sign * cur;
                sign = -1;
                cur = 0;
            }
            cur = 10 * cur + (c - '0');
        }
        ans += sign * cur;
        cout << ans << '\n';
    }
}

