#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(6) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n), indeg(n);
        for (auto& x : a) {
            cin >> x;
            --x;
            indeg[x]++;
        }
        int q;
        cin >> q;
        vector<int> ans(q);
        struct Query {
            ll m;
            int index;
        };
        vector<basic_string<Query>> queries(n);
        while (q--) {
            ll m;
            int y;
            cin >> m >> y;
            --y;
            queries[y].push_back(Query{m, q});
        }
        vector<int> leaves;
        leaves.reserve(n);
        vector<vector<int>> depth_count(n);
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) leaves.push_back(i);
            depth_count[i].push_back(1);
        }
        // don't care about b
        auto join = [](vector<int>& a, vector<int>& b) {
            if (a.size() < b.size()) a.swap(b);
            int bsz = (int)b.size();
            int asz = (int)a.size();
            for (int i = 0; i < bsz; ++i) a[asz - 1 - i] += b[bsz - 1 - i];
        };
        for (int i = 0; i < (int)leaves.size(); ++i) {
            int leaf = leaves[i];
            int max_depth = (int)depth_count[leaf].size() - 1;
            for (auto [m, index] : queries[leaf])
                if (m <= max_depth)
                    ans[index] = depth_count[leaf][max_depth - m];
            depth_count[leaf].push_back(0);
            join(depth_count[a[leaf]], depth_count[leaf]);
            vector<int>().swap(depth_count[leaf]);
            if (!(--indeg[a[leaf]])) leaves.push_back(a[leaf]);
        }
        // only cycles remain now
        for (int i = 0; i < n; ++i) {
            if (!indeg[i]) continue;
            // i is the cycle representative
            int sz = 0;
            int nxt = i;
            vector<int> after_cut_count;
            do {
                ++sz;
                indeg[nxt] = 0;
                auto v = depth_count[nxt];
                join(after_cut_count, v);
                after_cut_count.push_back(0);
                nxt = a[nxt];
            } while (nxt != i);
            assert(nxt == i);
            for (int j = (int)after_cut_count.size() - 1 - sz; j >= 0; --j)
                after_cut_count[j] += after_cut_count[j + sz];  // mod
            // traverse cycle
            do {
                join(after_cut_count, depth_count[nxt]);
                for (auto [m, index] : queries[nxt]) {
                    if (m >= (int)after_cut_count.size()) {
                        ans[index] = after_cut_count
                            [(((int)after_cut_count.size() - 1 - m) % sz + sz) %
                             sz];
                    } else {
                        ans[index] =
                            after_cut_count[(int)after_cut_count.size() - 1 -
                                            m];
                    }
                }
                after_cut_count.push_back(0);
                nxt = a[nxt];
            } while (nxt != i);
        }
        reverse(begin(ans), end(ans));
        for (auto x : ans) cout << x << '\n';
    }
}
