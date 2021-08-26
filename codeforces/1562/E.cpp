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

// z[i] is the length of the longest common prefix between s and the suffix of s
// starting at i.
std::vector<int> z_function(std::string s) {
    int n = (int)s.length();
    std::vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector zfuncs(n, vector<int>());
        for (int i = 0; i < n; ++i) zfuncs[i] = z_function(s.substr(i));
        vector<ll> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i] = 0;
            for (int j = 0; j < i; ++j) {
                if (s[j] < s[i]) {
                    dp[i] = max(dp[i], dp[j]);
                } else if (s[i] == s[j]) {
                    int val = zfuncs[j][i - j];
                    if (val != n - i && s[j + val] < s[i + val])
                        dp[i] = max(dp[i], dp[j] - val);
                }
            }
            dp[i] += n - i;
        }
        cout << *max_element(begin(dp), end(dp)) << '\n';
    }
}
