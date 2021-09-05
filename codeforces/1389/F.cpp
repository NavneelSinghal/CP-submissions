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
        int n;
        cin >> n;
        vector<int> l(n), r(n), t(n);
        vector<tuple<int, int, int>> events;
        events.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            cin >> l[i] >> r[i] >> t[i];
            --t[i];
            events.emplace_back(l[i], 0, i);
            events.emplace_back(r[i], 1, i);
        }
        sort(begin(events), end(events));
        int ans = n;
        vector<set<pair<int, int>>> s(2);
        for (auto [pos, event_type, i] : events) {
            auto type = t[i];
            if (event_type == 1) {
                auto other = t[i] ^ 1;
                // check if already deleted
                auto p = pair{r[i], i};
                if (s[type].find(p) != s[type].end()) {
                    if (!s[other].empty()) {
                        --ans;
                        s[other].erase(s[other].begin());
                    }
                    s[type].erase(p);
                }
            } else {
                s[type].insert(pair{r[i], i});
            }
        }
        cout << ans << '\n';
    }
}
