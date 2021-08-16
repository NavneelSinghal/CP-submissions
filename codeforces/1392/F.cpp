#include <numeric>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        ll sum = accumulate(begin(a), end(a), 0LL);
        ll sum_of_almost_equal = (sum - 1LL * n * (n - 1) / 2);
        ll equal_part = sum_of_almost_equal / n;
        ll unequal = sum_of_almost_equal % n;
        for (int i = 0; i < n; ++i) {
            if (i < unequal) {
                cout << i + 1 + equal_part << ' ';
            } else {
                cout << i + equal_part << ' ';
            }
        }
        cout << '\n';
    }
}

