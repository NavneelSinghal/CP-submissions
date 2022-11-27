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
        string s;
        cin >> s;
        int k;
        cin >> k;
        debug(s, k);
        int n = (int)s.size();
        bool first_removal = true;
        vector<array<int, 10>> next_pos(n);
        for (auto& x : next_pos)
            for (auto& y : x) y = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - 1) next_pos[i] = next_pos[i + 1];
            next_pos[i][s[i] - '0'] = i;
        }
        debug(next_pos);
        string ans = "";
        int pos = 0;
        while (pos < n) {
            int x = -1;
            for (int i = first_removal; i < 10; ++i) {
                if (next_pos[pos][i] == -1) continue;
                if (next_pos[pos][i] - pos <= k) {
                    x = next_pos[pos][i];
                    break;
                }
            }
            assert(x != -1);
            k -= x - pos;
            ans += s[x];
            pos = x + 1;
            first_removal = false;
        }
        while (k > 0) --k, ans.pop_back();
        cout << ans << '\n';
    }
}
