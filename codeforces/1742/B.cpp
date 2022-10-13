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
        i32 n;
        std::cin >> n;
        std::vector<i32> a(n);
        for (auto& x : a) std::cin >> x;
        std::sort(a.begin(), a.end());
        bool works = true;
        for (i32 i = 0; i + 1 < n; ++i) if (a[i] == a[i + 1]) {
            works = false;
            break;
        }
        if (works) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}
