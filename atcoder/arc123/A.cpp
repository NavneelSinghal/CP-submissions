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
        ll a, b, c;
        cin >> a >> b >> c;
        ll ans = 1e18;
        ans = min(ans, abs(a + c - 2 * b));
        if ((a & 1) == (c & 1)) {
            if (b < (a + c) / 2) ans = min(ans, abs(b - (a + c) / 2));
        } else {
            ll cur = 1;
            c++;
            cur += abs(b - (c + a) / 2);
            if (b < (a + c) / 2) ans = min(ans, cur);
        }
        cout << ans << '\n';
    }
}