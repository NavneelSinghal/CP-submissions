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

template <typename T>
struct Fenwick {
    int n;
    vector<T> t;
    Fenwick(int n) : n(n), t(n + 1) {}
    // prefix_sum[0..i]
    T query(int i) {
        T s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }
    // range query
    T query(int l, int r) { return query(r) - query(l - 1); }
    // increase a[i] by v
    void update(int i, T v) {
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        // count inversions
        ll n;
        cin >> n;
        vector<ll> loc(n);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            loc[x - 1] = i;
        }
        vector<ll> ans(n);
        Fenwick<ll> f(n);
        ll cur_inversions = 0;
        vector<set<ll>> s(2);
        vector<ll> sum(2);
        auto add = [&](int i, ll x) {
            s[i].insert(x);
            sum[i] += x;
        };
        auto remove = [&](int i, ll x) {
            s[i].erase(x);
            sum[i] -= x;
        };
        ll mid = -1;
        for (ll i = 0; i < n; ++i) {
            cur_inversions += i - f.query(loc[i]);
            ans[i] = cur_inversions;
            f.update(loc[i] + 1, 1);
            ll l_max = -1, r_min = 1e9;
            if (i >= 2) l_max = *s[0].rbegin(), r_min = *s[1].begin();
            if (i & 1) {
                // even number of elements
                ll add1 = mid;
                ll add2 = loc[i];
                if (add1 > add2) swap(add1, add2);
                if (add2 < l_max)
                    remove(0, l_max), add(1, l_max);
                else if (add1 > r_min)
                    remove(1, r_min), add(0, r_min);
                add(add1 > r_min, add1);
                add(add2 > l_max, add2);
                ans[i] += sum[1] - sum[0] - (1LL * (i + 1) * (i + 1)) / 4;
            } else {
                // odd number of elements
                if (loc[i] > r_min)
                    mid = r_min, remove(1, r_min), add(1, loc[i]);
                else if (loc[i] < l_max)
                    mid = l_max, remove(0, l_max), add(0, loc[i]);
                else
                    mid = loc[i];
                ans[i] += sum[1] - sum[0] - (1LL * (i + 1) * (i + 1) - 1) / 4;
            }
        }
        for (ll i = 0; i < n; ++i) cout << ans[i] << " \n"[i == n - 1];
    }
}

