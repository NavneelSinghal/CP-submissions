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
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        int mx = max_element(begin(a), end(a)) - begin(a);
        int mn = min_element(begin(a), end(a)) - begin(a);
        cout << min({max(mn, mx) + 1, n - min(mn, mx), n - mx + mn + 1,
                     n + mx - mn + 1})
             << '\n';
    }
}
