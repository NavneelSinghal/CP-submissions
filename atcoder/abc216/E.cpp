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

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        ll n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        sort(rbegin(a), rend(a));
        ll cur = 0;
        ll ans = 0;
        auto sum = [](ll x) {
            return x * (x + 1) / 2;
        };
        while (cur < n) {
            while (cur + 1 < n && a[cur + 1] == a[cur]) ++cur;
            // old to cur have the same things
            ll nxt = 0;
            if (cur < n - 1) nxt = a[cur + 1];
            ll total = (a[cur] - nxt) * 1LL * (cur + 1);
            ll rem = min((ll)k, total);
            if (rem == k) {
                ll layers = k / (cur + 1);
                ll remaining = k % (cur + 1);
                assert(layers <= a[cur]);
                ans += (cur + 1) * (sum(a[cur]) - sum(a[cur] - layers));
                ans += remaining * 1LL * (a[cur] - layers);
                break;
            } else {
                debug(ans);
                ans += (cur + 1) * (sum(a[cur]) - sum(nxt));  // something
                k -= total;
                debug(ans);
            }
            ++cur;
        }
        cout << ans << '\n';
    }
}

