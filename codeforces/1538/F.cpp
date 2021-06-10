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
        int l, r;
        cin >> l >> r;
        ll ans = 0;
        while (l != r) {
            ans += r - l;
            l /= 10;
            r /= 10;
        }
        cout << ans << '\n';
    }
}
