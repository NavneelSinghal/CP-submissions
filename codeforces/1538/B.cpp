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
        ll sum = accumulate(begin(a), end(a), 0LL);
        if (sum % n != 0) {
            cout << -1 << '\n';
        } else {
            sum /= n;
            auto it =
                remove_if(begin(a), end(a), [&](int x) { return x <= sum; });
            cout << it - begin(a) << '\n';
        }
    }
}
