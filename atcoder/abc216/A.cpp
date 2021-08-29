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
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string s;
        cin >> s;
        int a, b;
        if (s.size() == 4) {
            a = stoi(s.substr(0, 2));
            b = stoi(s.substr(3));
        } else if (s.size() == 3) {
            a = stoi(s.substr(0, 1));
            b = stoi(s.substr(2));
        }
        if (b <= 2) {
            cout << a << '-' << '\n';
        } else if (b <= 6) {
            cout << a << '\n';
        } else {
            cout << a << '+' << '\n';
        }
    }
}

