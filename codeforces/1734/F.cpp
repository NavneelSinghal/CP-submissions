#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using i128 = __int128;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f80 = long double;
using f128 = __float128;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    std::cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        std::map<std::pair<u64, u64>, u64> dp;
        auto rec = [&](auto self, u64 n, u64 m) -> u64 {
            if (m == 0)
                return 0;
            else if (m == 1)
                return std::popcount(n) & 1;
            else {
                auto args = std::pair{n, m};
                auto it = dp.find(args);
                if (it != dp.end())
                    return it->second;
                else if (m & 1)
                    return dp[args] =
                               self(self, n, m - 1) +
                               (std::popcount((m - 1) ^ (n + m - 1)) & 1);
                else if (n & 1)
                    return dp[args] = m - self(self, n >> 1, m >> 1) -
                                      self(self, (n >> 1) + 1, m >> 1);
                else
                    return dp[args] = 2 * self(self, n >> 1, m >> 1);
            }
        };
        uint64_t n, m;
        std::cin >> n >> m;
        std::cout << rec(rec, n, m) << '\n';
    }
}
