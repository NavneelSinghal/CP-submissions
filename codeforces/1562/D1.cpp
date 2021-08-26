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
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> sum(n + 1);
        for (int i = 0, par = 1; i < n; ++i, par *= -1) {
            sum[i + 1] = sum[i] + par * (int(s[i] == '+') - int(s[i] == '-'));
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            --l;
            if (sum[r] - sum[l] == 0) {
                cout << 0 << '\n';
            } else if ((sum[r] - sum[l]) & 1) {
                cout << 1 << '\n';
            } else {
                cout << 2 << '\n';
            }
        }
    }
}

