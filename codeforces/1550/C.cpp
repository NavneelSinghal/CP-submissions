#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;

using namespace std;

template <class T>
auto compress(const vector<T>& a) {
    int n = size(a);
    vector<pair<T, int>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    vector<T> vals;
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals.push_back(p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return make_pair(compressed, vals);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<int> nxt_ge(n, n);
        vector<int> nxt_le(n, n);
        stack<int> s;
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] < a[i]) s.pop();
            if (!s.empty()) nxt_ge[i] = s.top();
            s.push(i);
        }
        stack<int>().swap(s);
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] > a[i]) s.pop();
            if (!s.empty()) nxt_le[i] = s.top();
            s.push(i);
        }
        vector<int> closest_ge(n, n);
        vector<int> closest_le(n, n);
        const auto rec = [&](const auto& self, int l, int r) -> void {
            if (l >= r) return;
            int m = (l + r + 1) / 2;
            // [l, m - 1] and [m, r]
            // compress a[l..r]
            vector<int> temp(a.begin() + l, a.begin() + r + 1);
            auto [compressed, vals] = compress(temp);
            int sz = temp.size();
            vector<int> min_nxt_le(sz, n);
            vector<int> min_nxt_ge(sz, n);
            // min_nxt_le[i] = min nxt_le(val[i])
            // min_nxt_ge[i] = min mxt_ge(val[i])
            for (int i = m; i <= r; ++i) {
                int loc =
                    lower_bound(begin(vals), end(vals), a[i]) - begin(vals);
                min_nxt_le[loc] = min(min_nxt_le[loc], nxt_le[i]);
                min_nxt_ge[loc] = min(min_nxt_ge[loc], nxt_ge[i]);
            }
            // prefix min
            for (int i = 1; i < sz; ++i)
                min_nxt_le[i] = min(min_nxt_le[i], min_nxt_le[i - 1]);
            for (int i = sz - 2; i >= 0; --i)
                min_nxt_ge[i] = min(min_nxt_ge[i], min_nxt_ge[i + 1]);
            for (int i = l; i < m; ++i) {
                int loc =
                    lower_bound(begin(vals), end(vals), a[i]) - begin(vals);
                closest_le[i] = min(closest_le[i], min_nxt_le[loc]);
                closest_ge[i] = min(closest_ge[i], min_nxt_ge[loc]);
            }
            if (l < m - 1) self(self, l, m - 1);
            if (m < r) self(self, m, r);
        };
        rec(rec, 0, n - 1);
        ll ans = 0;
        multiset<int> ms_ge, ms_le;
        int r = 0;
        for (int i = 0; i < n; ++i) {
            while (r < n && (ms_le.empty() || *ms_le.begin() > r) &&
                   (ms_ge.empty() || *ms_ge.begin() > r)) {
                ms_le.insert(closest_le[r]);
                ms_ge.insert(closest_ge[r]);
                ++r;
            }
            ans += r - i;
            ms_le.erase(ms_le.find(closest_le[i]));
            ms_ge.erase(ms_ge.find(closest_ge[i]));
        }
        cout << ans << '\n';
    }
}