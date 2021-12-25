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
using ld = long double;

using namespace std;

template <typename I, typename P, bool b>
I bin_search_split(I l, I r, const P& predicate) {
    --l, ++r;
    while (r - l > 1) {
        auto mid = l + (r - l) / 2;
        if (predicate(mid))
            l = mid;
        else
            r = mid;
    }
    if constexpr (b) {
        return r;
    } else {
        return l;
    }
}

// returns first i in [l, r], p(i) false, and if none found, returns r + 1
template <typename I, typename P>
I find_first_false(I l, I r, const P& p) {
    return bin_search_split<I, P, true>(l, r, p);
}

// returns last i in [l, r], p(i) true, and if none found, returns l - 1
template <typename I, typename P>
I find_last_true(I l, I r, const P& p) {
    return bin_search_split<I, P, false>(l, r, p);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";

        constexpr int N = 100000;

        set<pair<int, int>> points;

        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            points.emplace(x + y, x - y + N);
        }

        vector<vector<int>> Y((2 * N + 1) << 2);

        auto build = [&](const auto& self, int i, int l, int r) -> void {
            if (l + 1 == r) {
                auto it = points.lower_bound({l, 0});
                while (it != points.end() && it->first == l)
                    Y[i].push_back(it->second), ++it;
            } else {
                self(self, 2 * i, l, (l + r) / 2);
                self(self, 2 * i + 1, (l + r) / 2, r);
                Y[i].resize(Y[2 * i].size() + Y[2 * i + 1].size());
                merge(Y[2 * i].begin(), Y[2 * i].end(), Y[2 * i + 1].begin(),
                      Y[2 * i + 1].end(), Y[i].begin());
            }
        };

        build(build, 1, 0, 2 * N + 1);

        // query [x1, x2) * [y1, y2)
        auto query = [&](const auto& self, int x1, int y1, int x2, int y2,
                         int i, int l, int r) -> int {
            if (x2 <= l || r <= x1)
                return 0;
            else if (x1 <= l && r <= x2)
                return int(lower_bound(begin(Y[i]), end(Y[i]), y2) -
                           lower_bound(begin(Y[i]), end(Y[i]), y1));
            else
                return self(self, x1, y1, x2, y2, 2 * i, l, (l + r) / 2) +
                       self(self, x1, y1, x2, y2, 2 * i + 1, (l + r) / 2, r);
        };

        int q;
        cin >> q;

        while (q--) {
            int x, y, k;
            cin >> x >> y >> k;
            tie(x, y) = make_pair(x + y, x - y + N);
            cout << find_first_false(0, 2 * N - 1, [&](int m) {
                return query(query, x - m, y - m, x + m + 1, y + m + 1, 1, 0,
                             2 * N + 1) < k;
            }) << '\n';
        }
    }
}
