#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int l, r;
        cin >> l >> r;
        // b, b + x
        if (r < 2 * l - 1) {
            cout << (r % l) << '\n';
        } else {
            // 2 * x - 1 <= r
            // x = (r + 1) / 2
            int x = (r + 1) / 2;
            cout << x - 1 << '\n';
        }
    }
}

