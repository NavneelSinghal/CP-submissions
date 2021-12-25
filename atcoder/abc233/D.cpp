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
        int n;
        cin >> n;
        ll k;
        cin >> k;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        vector<ll> pre(n + 1);
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i - 1];
        map<ll, int> freq;
        freq[0] = 1;
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            // end = i
            ans += freq[pre[i] - k];
            freq[pre[i]]++;
        }
        cout << ans << '\n';
    }
}
