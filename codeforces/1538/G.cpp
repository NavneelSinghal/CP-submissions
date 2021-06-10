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
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        if (a == b) {
            cout << min(x, y) / a << '\n';
        } else {
            if (a < b) swap(a, b);
            int l = 0;
            int r = x + y + 1;
            while (r - l > 1) {
                ll m = (1LL * l + r) / 2;
                ll dx = x - ll(b) * m, dy = y - ll(b) * m;
                if (dx >= 0 && dy >= 0 && dx / (a - b) + dy / (a - b) >= m) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << l << '\n';
        }
    }
}
