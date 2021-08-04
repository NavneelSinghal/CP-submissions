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
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        vector<ll> ans(n);
        vector<ll> loc(n);
        for (ll i = 0; i < n; ++i) loc[a[i] - 1] = i;
        Fenwick<ll> f(n);
        ll cur_inversions = 0;
        set<ll> l, r;
        ll l_sum = 0, r_sum = 0;
        ll mid = -1;
        for (ll i = 0; i < n; ++i) {
            cur_inversions += i - f.query(loc[i]);
            ans[i] = cur_inversions;
            debug(ans[i]);
            f.update(loc[i] + 1, 1);
            if (i & 1) {
                // even number of elements
                ll add1 = mid;
                ll add2 = loc[i];
                if (add1 > add2) swap(add1, add2);
                if (i == 1) {
                    l.insert(add1);
                    r.insert(add2);
                    l_sum += add1;
                    r_sum += add2;
                } else {
                    ll l_max = *l.rbegin();
                    ll r_min = *r.begin();
                    if (add2 < l_max) {
                        l.erase(l_max);
                        l_sum -= l_max;
                        r.insert(l_max);
                        r_sum += l_max;
                        l.insert(add1);
                        l.insert(add2);
                        l_sum += add1;
                        l_sum += add2;
                    } else if (add1 > r_min) {
                        r.erase(r_min);
                        r_sum -= r_min;
                        l.insert(r_min);
                        l_sum += r_min;
                        r.insert(add1);
                        r.insert(add2);
                        r_sum += add1;
                        r_sum += add2;
                    } else {
                        l.insert(add1);
                        r.insert(add2);
                        l_sum += add1;
                        r_sum += add2;
                    }
                }
                ans[i] += r_sum - l_sum - (1LL * (i + 1) * (i + 1)) / 4;
            } else {
                // odd number of elements
                if (i == 0) {
                    mid = loc[i];
                } else {
                    ll l_max = *l.rbegin();
                    ll r_min = *r.begin();
                    if (loc[i] > r_min) {
                        mid = r_min;
                        r.erase(r_min);
                        r_sum -= r_min;
                        r.insert(loc[i]);
                        r_sum += loc[i];
                    } else if (loc[i] < l_max) {
                        mid = l_max;
                        l.erase(l_max);
                        l_sum -= l_max;
                        l.insert(loc[i]);
                        l_sum += loc[i];
                    } else {
                        mid = loc[i];
                    }
                }
                ans[i] += r_sum - l_sum - (1LL * (i + 1) * (i + 1) - 1) / 4;
            }
        }
        for (ll i = 0; i < n; ++i) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

