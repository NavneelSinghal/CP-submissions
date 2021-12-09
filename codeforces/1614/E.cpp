#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();

using ll = long long;
using ld = long double;

using namespace std;

#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

namespace pbds {
    using namespace __gnu_pbds;
#ifdef PB_DS_ASSOC_CNTNR_HPP
    template <class Key, class Value, class Hash>
    using unordered_map = gp_hash_table<
        Key, Value, Hash, std::equal_to<Key>, direct_mask_range_hashing<>,
        linear_probe_fn<>,
        hash_standard_resize_policy<hash_exponential_size_policy<>,
                                    hash_load_check_resize_trigger<>, true>>;
    template <class Key, class Hash>
    using unordered_set = pbds::unordered_map<Key, null_type, Hash>;
#endif
#ifdef PB_DS_TREE_POLICY_HPP
    template <typename T>
    using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag,
                             tree_order_statistics_node_update>;
    template <typename T>
    using ordered_multiset = tree<T, null_type, std::less_equal<T>, rb_tree_tag,
                                  tree_order_statistics_node_update>;
    template <class Key, class Value, class Compare = std::less<Key>>
    using ordered_map = tree<Key, Value, Compare, rb_tree_tag,
                             tree_order_statistics_node_update>;
    // find_by_order(k)  returns iterator to kth element starting from 0;
    // order_of_key(k) returns count of elements strictly smaller than k;
    // for ordered_multiset, lower_bound and upper_bound swap roles
#endif
}  // namespace pbds

namespace hashing {

    // #define USE_AES 0
    /* append to top
    #define USE_AES 1
    #if USE_AES
        #pragma GCC target("aes")
        #include <immintrin.h>
    #endif
    */

    using ll = std::int64_t;
    using ull = std::uint64_t;
    static const ull FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();

#if USE_AES
    std::mt19937 rd(FIXED_RANDOM);
    const __m128i KEY1{(ll)rd(), (ll)rd()};
    const __m128i KEY2{(ll)rd(), (ll)rd()};
#endif

    template <class T, class D = void>
    struct custom_hash {};

    // https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
    template <class T>
    inline void hash_combine(ull& seed, const T& v) {
        custom_hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4);
    };

    // http://xorshift.di.unimi.it/splitmix64.c
    template <class T>
    struct custom_hash<
        T, typename std::enable_if<std::is_integral<T>::value>::type> {
        ull operator()(T _x) const {
            ull x = _x;
#if USE_AES
            // implementation defined till C++17, defined from C++20
            __m128i m{ll(ull(x) * 0xbf58476d1ce4e5b9ULL), (ll)FIXED_RANDOM};
            __m128i y = _mm_aesenc_si128(m, KEY1);
            __m128i z = _mm_aesenc_si128(y, KEY2);
            return z[0];
#else
            x += 0x9e3779b97f4a7c15 + FIXED_RANDOM;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
#endif
        }
    };

    template <class T>
    struct custom_hash<T,
                       std::void_t<decltype(std::begin(std::declval<T>()))>> {
        ull operator()(const T& a) const {
            ull value = FIXED_RANDOM;
            for (auto& x : a) hash_combine(value, x);
            return value;
        }
    };

    template <class... T>
    struct custom_hash<std::tuple<T...>> {
        ull operator()(const std::tuple<T...>& a) const {
            ull value = FIXED_RANDOM;
            std::apply(
                [&value](T const&... args) {
                    (hash_combine(value, args), ...);
                },
                a);
            return value;
        }
    };

    template <class T, class U>
    struct custom_hash<std::pair<T, U>> {
        ull operator()(const std::pair<T, U>& a) const {
            ull value = FIXED_RANDOM;
            hash_combine(value, a.first);
            hash_combine(value, a.second);
            return value;
        }
    };

};  // namespace hashing

// 0-based indexing for API
// 1-based indexing for internals
template <typename T>
struct Fenwick {
    ll n;
    pbds::unordered_map<ll, T, hashing::custom_hash<ll>> t;
    Fenwick(ll n) : n(n) {}
    // prefix sum [0, i)
    T query(ll i) {
        T s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }
    // range query [l, r)
    T query(ll l, ll r) { return query(r) - query(l); }
    // increase a[i] by v
    void update(ll i, T v) {
        ++i;
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }

    // assumes f is monotonic - TT...TFF...F
    // returns the max r > 0 such that f(query([0, r)), r) is true
    // returns 0 if no such positive r exists
    template <class F>
    ll max_right(F&& f) {
        T sum = 0;
        ll pos = 0;
        for (ll i = __lg(n); i >= 0; --i) {
            if (pos + (1LL << i) <= n) {
                T s = sum + t[pos + (1LL << i)];
                if (f(s, pos + (1LL << i))) {
                    pos += (1LL << i);
                    sum = s;
                }
            }
        }
        return pos;
    }
};

int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;

        constexpr ll mod = int(1e9) + 1;
        Fenwick<ll> f(mod + 2);

        ll lastans = 0;

        while (n--) {
            int t, k;
            cin >> t >> k;

            // offset[i] = sum[0, i]

            // last i such that sum[0, i] + i < t
            // = -1 + last i such that query(0, i) + i - 1 < t
            // first i such that sum[0, i] + i > t
            // = -1 + first i such that query(0, i) + i - 1 > t
            // = last i such that query(0, i) + i - 1 <= t

            ll l = f.max_right([&](ll val, ll i) { return val + i - 1 < t; });
            ll r = f.max_right([&](ll val, ll i) { return val + i - 1 <= t; });

            // [0, l - 1] -> range add +1
            // [l, r - 1] -> range add 0
            // [r, inf) -> range add -1

            f.update(0, +1);
            f.update(l, -1);
            f.update(r, -1);

            while (k--) {
                int x;
                cin >> x;
                x = (lastans + x) % mod;
                lastans = f.query(x + 1) + x;
                cout << lastans << '\n';
            }
        }
    }
}
