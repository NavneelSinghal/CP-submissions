#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        string s;
        cin >> n >> s;
        if (n % 3 == 2) {
            cout << "NO\n";
            continue;
        }
        bool works = true;
        for (int i = 0; i < n; i += 3) {
            if (i + 2 < n) {
                if (s[i + 1] != s[i + 2]) {
                    works = false;
                    break;
                }
            }
        }
        cout << (works ? "YES\n" : "NO\n");
    }
}
