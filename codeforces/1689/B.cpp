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
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> p(n);
        for (auto& x : p) cin >> x;
        if (n == 1) {
            cout << -1 << '\n';
        } else {
            vector<int> a(n);
            iota(begin(a), end(a), 1);
            for (int i = 0; i + 1 < n; ++i)
                if (p[i] == a[i]) swap(a[i], a[i + 1]);
            if (p[n - 1] == a[n - 1]) swap(a[n - 2], a[n - 1]);
            for (auto x : a) cout << x << ' ';
            cout << '\n';
        }
    }
}

