#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 5e9;

template <class T>
struct range_vector {
    int min_index;
    vector<T> data;
    range_vector(int _min_index, int _max_index, T&& values = T())
        : data(_max_index - _min_index + 1, values), min_index(_min_index) {
        assert(_min_index <= _max_index + 1);
    }
    T& operator[](int i) { return data[i - min_index]; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; ++_t) {
        int n, mod;
        cin >> n >> mod;
        int total_pairs = n * (n - 1) / 2;
        range_vector<ll> dp(-total_pairs, total_pairs);
        dp[0] = 1 % mod;
        ll ans = 0;
        auto reduce = [&mod](ll& x) -> void {
            if (x >= mod) x -= mod;
        };
        auto add = [&reduce](ll& a, ll b) -> void {
            a += b;
            reduce(a);
        };
        auto subtract = [&add, &mod](ll& a, ll b) -> void {
            add(a, mod - b);
        };
        for (int i = 1; i <= n; ++i) {
            ll cur = 0;
            int pairs = (i - 2) * (i - 1) / 2;
            for (int inversions = 1; inversions <= pairs; ++inversions) {
                int k = min(i, inversions);
                cur += (i * (i - 1) / 2 - (i - k) * (i - k + 1) / 2) *
                       dp[inversions];
                cur %= mod;
            }
            for (int inversions = i + 1; inversions <= n; ++inversions)
                (cur *= inversions) %= mod;
            add(ans, cur);
            pairs += i - 1;
            for (int inversions = pairs; inversions >= i - pairs; --inversions)
                subtract(dp[inversions], dp[inversions - i]);
            for (int inversions = -pairs + 1; inversions <= pairs; ++inversions)
                add(dp[inversions], dp[inversions - 1]);
            for (int inversions = -pairs; inversions <= pairs - i; ++inversions)
                subtract(dp[inversions], dp[inversions + i]);
            for (int inversions = pairs - 1; inversions >= -pairs; --inversions)
                add(dp[inversions], dp[inversions + 1]);
        }
        cout << ans << '\n';
    }
    return 0;
}