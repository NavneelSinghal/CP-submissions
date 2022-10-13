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
        std::array<std::vector<i32>, 31> pos{};
        std::vector<u32> a(n);
        for (i32 i = 0; i != n; ++i) {
            std::cin >> a[i];
            for (i32 j = 0; j != 31; ++j) {
                if (a[i] >> j & 1) {
                    pos[j].push_back(i);
                }
            }
        }
        debug(pos);
        std::vector<bool> used(n);
        u32 marked = 0;
        for (i32 i = 0; i != n; ++i) {
            bool has = false;
            std::vector<i32> here;
            for (i32 j = 30; j >= 0; --j) {
                if (!(marked >> j & 1)) {
                    if (not has and not pos[j].empty()) {
                        here = pos[j];
                        has = true;
                    } else if (not pos[j].empty()) {
                        std::vector<i32> use;
                        for (auto x : here) {
                            if (std::binary_search(pos[j].begin(), pos[j].end(),
                                                   x)) {
                                use.push_back(x);
                            }
                        }
                        if (not use.empty()) here = std::move(use);
                    }
                }
            }
            debug(here);
            if (here.empty()) {
                break;
            } else {
                i32 x = here[0];
                used[x] = true;
                marked |= a[x];
                std::cout << a[x] << ' ';
                for (auto& p : pos) {
                    auto it = std::find(p.begin(), p.end(), x);
                    if (it != p.end()) p.erase(it);
                }
            }
        }
        for (i32 i = 0; i != n; ++i)
            if (!used[i]) {
                std::cout << a[i] << ' ';
            }
        std::cout << '\n';
    }
}
