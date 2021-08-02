#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, m;
        cin >> n >> m;
        vector<int> mark(n, -1);
        vector<pair<int, int>> unsorted;
        for (int i = 0; i < m; ++i) {
            int type, l, r;
            cin >> type >> l >> r;
            --l, --r;
            if (type == 1) {
                for (int j = l; j < r; ++j) mark[j] = 0;
            } else {
                unsorted.emplace_back(l, r);
            }
        }
        vector<int> a(n, n);
        for (int i = 1; i < n; ++i) a[i] = a[i - 1] + mark[i - 1];
        bool works = true;
        for (auto [l, r] : unsorted) {
            if (is_sorted(begin(a) + l, begin(a) + r + 1)) {
                works = false;
                break;
            }
        }
        if (!works)
            cout << "NO\n";
        else {
            cout << "YES\n";
            for (auto& x : a) cout << x << ' ';
            cout << '\n';
        }
    }
}
