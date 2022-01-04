#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

namespace internal {

    // @param m `1 <= m`
    // @return x mod m
    constexpr ll safe_mod(ll x, ll m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }
    // @param n `n < 2^32`
    // @param m `1 <= m < 2^32`
    // @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
    ull floor_sum_unsigned(ull n, ull m, ull a, ull b) {
        ull ans = 0;
        while (true) {
            if (a >= m) {
                ans += n * (n - 1) / 2 * (a / m);
                a %= m;
            }
            if (b >= m) {
                ans += n * (b / m);
                b %= m;
            }

            ull y_max = a * n + b;
            if (y_max < m) break;
            // y_max < m * (n + 1)
            // floor(y_max / m) <= n
            n = (ull)(y_max / m);
            b = (ull)(y_max % m);
            std::swap(m, a);
        }
        return ans;
    }

}  // namespace internal

ll floor_sum(ll n, ll m, ll a, ll b) {
    assert(0 <= n && n < (1LL << 32));
    assert(1 <= m && m < (1LL << 32));
    ull ans = 0;
    if (a < 0) {
        ull a2 = internal::safe_mod(a, m);
        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        ull b2 = internal::safe_mod(b, m);
        ans -= 1ULL * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + internal::floor_sum_unsigned(n, m, a, b);
}

template <typename I, typename P, bool b>
I bin_search_split(I l, I r, const P& predicate) {
    --l, ++r;
    while (r - l > 1) {
        auto mid = l + (r - l) / 2;
        if (predicate(mid))
            l = mid;
        else
            r = mid;
    }
    if constexpr (b) {
        return r;
    } else {
        return l;
    }
}

// returns first i in [l, r], p(i) false, and if none found, returns r + 1
template <typename I, typename P>
I find_first_false(I l, I r, const P& p) {
    return bin_search_split<I, P, true>(l, r, p);
}

// returns last i in [l, r], p(i) true, and if none found, returns l - 1
template <typename I, typename P>
I find_last_true(I l, I r, const P& p) {
    return bin_search_split<I, P, false>(l, r, p);
}

// find least solution to (ax + b) mod m > r
// return -1 if it doesn't exist
constexpr auto find_least_sol = [](auto a, auto b, auto m, auto r) {
    using T = decltype(m);

    if (r >= m - 1) return T(-1);

    b %= m;
    if (b < 0) b += m;
    if (b > r) return T(0);

    a %= m;
    if (a < 0) a += m;
    if (a == 0) return T(-1);

    auto g = std::gcd(a, m);
    auto b_g = b % g;
    if (m - g + b_g <= r) return T(-1);

    return find_last_true(T(1), m + 1, [&](auto x) {
        return floor_sum(x, m, a, b) == x + floor_sum(x, m, a, b - r - 1);
    });
};

constexpr auto solve = [](auto a, auto b, auto v, auto m) {
    auto x = find_least_sol(a, v, b, m - a);
    debug(x);
    assert(x != -1);
    return (a * x + v) / b - v / b + x;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";

        ll a, b, v, m;
        cin >> a >> b >> v >> m;

        if (a + b <= m + 1) {
            cout << m + 1 << '\n';
            continue;
        }

        if (a > m) {
            cout << v / b + (m - v) / b + 1 << '\n';
            continue;
        }

        if (b > m) {
            cout << v / a + (m - v) / a + 1 << '\n';
            continue;
        }

        v %= a;

        cout << solve(a, b, v, m) + solve(b, a, v, m) + 1 << '\n';
    }
}
