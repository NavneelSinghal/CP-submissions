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
        int n, m, k;
        cin >> n >> m >> k;
        string s, t;
        cin >> s >> t;
        sort(begin(s), end(s)), sort(begin(t), end(t));
        string ans = "";
        int moves = 0;
        int prv = -1;
        for (int i = 0, j = 0; i < n && j < m;) {
            if (s[i] < t[j]) {
                if (prv == 0 && moves == k) {
                    ans += t[j++];
                    prv = 1;
                    moves = 1;
                } else {
                    if (prv == 0)
                        moves++;
                    else
                        moves = 1, prv = 0;
                    ans += s[i++];
                }
            } else {
                if (prv == 1 && moves == k) {
                    ans += s[i++];
                    prv = 0;
                    moves = 1;
                } else {
                    if (prv == 1)
                        moves++;
                    else
                        moves = 1, prv = 1;
                    ans += t[j++];
                }
            }
        }
        cout << ans << '\n';
    }
}

