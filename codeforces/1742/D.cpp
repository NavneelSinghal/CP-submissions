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
    // std::cout << std::setprecision(20) << std::fixed;
    i32 _tests = 1;
    std::cin >> _tests;
    for (i32 _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        std::vector<std::basic_string<i32>> pos(1001);
        i32 n;
        std::cin >> n;
        for (i32 i = 0; i != n; ++i) {
            i32 x;
            std::cin >> x;
            pos[x].push_back(i);
        }
        i32 ans = -1;
        for (i32 i = 1; i <= 1000; ++i) {
            for (i32 j = i; j <= 1000; ++j) {
                if (not pos[i].empty() and not pos[j].empty() and std::gcd(i, j) == 1) {
                    ans = std::max(ans, pos[i].back() + pos[j].back() + 2);
                }
            }
        }
        std::cout << ans << '\n';
    }
}
