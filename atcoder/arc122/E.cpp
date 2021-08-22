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
    cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        bool works = true;
        for (int i = n - 1; i >= 0; --i) {
            int index = -1;
            for (int j = 0; j <= i; ++j) {
                ll l = 1;
                for (int k = 0; k <= i; ++k) {
                    if (j == k) continue;
                    l = lcm(l, gcd(a[j], a[k]));
                }
                if (l < a[j]) {
                    index = j;
                    break;
                }
            }
            if (index == -1) {
                works = false;
                break;
            } else {
                swap(a[i], a[index]);
            }
        }
        if (!works) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (auto x : a) cout << x << ' ';
            cout << '\n';
        }
    }
}

