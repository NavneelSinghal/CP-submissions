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
    int _tests = 1;
    cin >> _tests;
    constexpr int N = 2e6 + 10;
    constexpr int M = 1e6;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        bitset<N> b;
        vector<int> ans;
        for (int i = 1; i <= M; ++i) {
            if ((int)ans.size() == n) break;
            if (b[i]) continue;
            ans.push_back(i);
            for (auto j : a)
                for (auto k : a)
                    if (i + j - k >= 0) b[i + j - k] = true;
        }
        cout << "YES\n";
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }
}

