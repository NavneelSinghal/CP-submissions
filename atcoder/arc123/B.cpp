#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        vector<int> a(n), b(n), c(n);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;
        for (auto& x : c) cin >> x;
        sort(begin(a), end(a));
        multiset<int> m = multiset<int>(begin(b), end(b));
        int cur = 0;
        for (; cur < n; ++cur) {
            auto it = m.upper_bound(a[cur]);
            if (it == m.end()) break;
            b[cur] = *it;
            m.erase(it);
        }
        m = multiset<int>(begin(c), end(c));
        int ans = 0;
        for (; ans < cur; ++ans) {
            auto it = m.upper_bound(b[ans]);
            if (it == m.end()) break;
            m.erase(it);
        }
        cout << ans << '\n';
    }
}