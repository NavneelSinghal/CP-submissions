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
        int n;
        cin >> n;
        string a;
        cin >> a;
        // if there is a 0 in the second half, done
        int r = -1;
        for (int i = n / 2; i < n; ++i) {
            if (a[i] == '0') {
                r = i;
                break;
            }
        }
        if (r == -1) {
            int cnt1 = 0;
            for (auto x : a) if (x == '1') cnt1++;
            if (cnt1 == n) {
                cout << 1 << ' ' << n / 2 << ' ' << 2 << ' ' << n / 2 + 1 << '\n';
            } else {
                int w = -1;
                for (int i = n - 1; i >= 0; --i) {
                    if (a[i] == '0') {
                        w = i;
                    }
                }
                assert(w != -1);
                cout << w + 1 << ' ' << n << ' ' << w + 2 << ' ' << n << '\n';
            }
        } else {
            cout << 1 << ' ' << r + 1 << ' ' << 1 << ' ' << r << '\n';
        }
    }
}

