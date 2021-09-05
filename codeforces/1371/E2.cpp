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
        int n, p;
        cin >> n >> p;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        int m = *max_element(begin(a), end(a));
        int offset = max(0, m - n);
        vector<int> freq(2 * n + 2);
        for (auto& x : a) freq[max(0, x - offset)]++;
        for (int i = 1; i <= 2 * n; ++i) freq[i] += freq[i - 1];
        for (int i = 0; i <= 2 * n; ++i)
            freq[i] = ((i + offset - freq[i]) % p + p) % p;
        vector<int> cnt(p);
        for (int i = 0; i < n; ++i) cnt[freq[i]]++;
        vector<int> ans;
        for (int x = offset; x <= m; ++x) {
            int t = x - offset;
            if (cnt[(x % p)] == 0) ans.push_back(x);
            cnt[freq[t]]--;
            cnt[freq[t + n]]++;
        }
        cout << ans.size() << '\n';
        for (auto& x : ans) cout << x << ' ';
        cout << '\n';
    }
}
