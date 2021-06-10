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
        int a, b, k;
        cin >> a >> b >> k;
        auto fac = [](int x) {
            int ans = 0;
            for (int i = 2; i * i <= x; ++i) {
                int freq = 0;
                while (x % i == 0) {
                    x /= i;
                    ans++;
                }
            }
            if (x > 1) ans++;
            return ans;
        };
        int g = __gcd(a, b);
        a /= g;
        b /= g;
        if (k == 1) {
            if (a == b || (a != 1 && b != 1))
                cout << "No\n";
            else
                cout << "Yes\n";
        } else {
            int faca = fac(a), facb = fac(b), facg = fac(g);
            if (faca + facb + 2 * facg >= k) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}
