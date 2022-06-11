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
        for (auto& x : p) cin >> x, --x;
        if (n == 1) {
            cout << -1 << '\n';
        } else {
            set<int> s;
            for (int i = 0; i < n; ++i) s.insert(i);
            for (int i = 0; i < n - 2; ++i) {
                auto it = s.begin();
                if (*it == p[i]) {
                    s.erase(it);
                    it = s.begin();
                    cout << *it + 1 << ' ';
                    s.erase(it);
                    s.insert(p[i]);
                } else {
                    cout << *it + 1 << ' ';
                    s.erase(it);
                }
            }
            assert(s.size() == 2);
            vector<int> rem{s.begin(), s.end()};
            if (rem[0] == p[n - 2] || rem[1] == p[n - 1])
                cout << rem[1] + 1 << ' ' << rem[0] + 1 << '\n';
            else
                cout << rem[0] + 1 << ' ' << rem[1] + 1 << '\n';
        }
    }
}

