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
        string s;
        cin >> s;
        int n = (int)s.size();
        vector<ll> pre(n);
        pre[0] = s[0] - '0';
        for (int i = 1; i < n; ++i) {
            pre[i] = pre[i - 1] + s[i] - '0';
        }
        reverse(begin(pre), end(pre));
        ll carry = 0;
        for (int i = 0; i < n; ++i) {
            ll x = pre[i] + carry;
            carry = x / 10;
            pre[i] = x % 10;
        }
        while (carry) {
            pre.emplace_back(carry % 10);
            carry /= 10;
        }
        reverse(begin(pre), end(pre));
        for (auto x : pre) cout << x;
        cout << '\n';
    }
}
