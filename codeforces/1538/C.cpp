#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 2e9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll t = 1;
    cin >> t;
    while (t--) {
        int n, l, r;
        cin >> n >> l >> r;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        sort(begin(a), end(a));
        ll ans = 0;
        for (auto x : a) {
            ans += upper_bound(begin(a), end(a), r - x) - begin(a);
            ans -= lower_bound(begin(a), end(a), l - x) - begin(a);
            if (l <= 2 * x && 2 * x <= r) --ans;
        }
        cout << ans / 2 << '\n';
    }
}
