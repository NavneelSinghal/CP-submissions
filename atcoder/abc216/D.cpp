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
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(m);
        vector<vector<int>> below(n);
        set<int> one, two;
        for (auto& x : a) {
            int k;
            cin >> k;
            x.resize(k);
            for (auto& y : x) cin >> y, --y;
            for (int i = 1; i < k; ++i) below[x[i - 1]].push_back(x[i]);
            if (one.find(x[0]) == one.end()) {
                one.insert(x[0]);
            } else {
                one.erase(x[0]);
                two.insert(x[0]);
            }
        }
        bool works = true;
        for (int i = 0; i < n; ++i) {
            if (two.empty()) {
                works = false;
                break;
            }
            int rem = *two.begin();
            two.erase(rem);
            for (auto x : below[rem]) {
                if (one.find(x) == one.end()) {
                    one.insert(x);
                } else {
                    one.erase(x);
                    two.insert(x);
                }
            }
        }
        if (works) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

