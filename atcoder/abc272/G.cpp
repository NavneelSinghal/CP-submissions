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

template <class T, class D = void>
struct bigger_type {};
template <class T>
struct bigger_type<T, std::enable_if_t<sizeof(T) <= 4, void>> {
    using type = std::uint64_t;
};
template <class T>
struct bigger_type<T, std::enable_if_t<4 < sizeof(T) && sizeof(T) <= 8, void>> {
    using type = __uint128_t;
};

template <class T>
struct lehmer {
    using U = typename bigger_type<T>::type;
    using result_type = T;
    using state_type = U;
    state_type state;
    static constexpr T MAGIC =
        (sizeof(T) >= 8 ? 0xda942042e4dd58b5 : 0xe4dd58b5);
    static constexpr std::size_t shift_size = (sizeof(T) >= 8 ? 64 : 32);
    constexpr lehmer(state_type state_ = default_seed) : state{state_} {}
    constexpr result_type operator()() {
        state *= MAGIC;
        return state >> shift_size;
    }
    constexpr void seed(state_type s) { state = s; }
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    constexpr friend bool operator==(const lehmer& a, const lehmer& b) {
        return a.state == b.state;
    }
    constexpr friend bool operator!=(const lehmer& a, const lehmer& b) {
        return a.state != b.state;
    }
    static constexpr state_type default_seed = 0;
};

template <class T>
struct wyhash {
    using U = typename bigger_type<T>::type;
    using result_type = T;
    using state_type = U;
    state_type state;
    static constexpr T MAGIC_INCREMENT =
        (sizeof(T) >= 8 ? 0x60bee2bee120fc15 : 0xe120fc15);
    static constexpr T MAGIC_MULTIPLY1 =
        (sizeof(T) >= 8 ? 0xa3b195354a39b70d : 0x4a39b70d);
    static constexpr T MAGIC_MULTIPLY2 =
        (sizeof(T) >= 8 ? 0x1b03738712fad5c9 : 0x12fad5c9);
    static constexpr std::size_t shift_size = (sizeof(T) >= 8 ? 64 : 32);

    constexpr wyhash(state_type state_ = default_seed) : state{state_} {}
    constexpr result_type operator()() {
        state += MAGIC_INCREMENT;
        U tmp = static_cast<U>(state) * MAGIC_MULTIPLY1;
        result_type m1 = static_cast<result_type>((tmp >> shift_size) ^ tmp);
        tmp = static_cast<U>(m1) * MAGIC_MULTIPLY2;
        result_type m2 = static_cast<result_type>((tmp >> shift_size) ^ tmp);
        return m2;
    }
    constexpr void discard(std::uint64_t steps) {
        state +=
            static_cast<state_type>(static_cast<U>(MAGIC_INCREMENT) * steps);
    }
    constexpr void seed(state_type s) { state = s; }
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    constexpr friend bool operator==(const wyhash& a, const wyhash& b) {
        return a.state == b.state;
    }
    constexpr friend bool operator!=(const wyhash& a, const wyhash& b) {
        return a.state != b.state;
    }
    static constexpr state_type default_seed = 0;
};

template <class RNG>
struct Random : RNG {
    using RNG::operator();
    Random() : RNG(gen_seed()) {}

    static std::uint64_t gen_seed() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

    using T = typename RNG::result_type;
    using U = typename bigger_type<T>::type;
    static constexpr std::size_t shift_size = CHAR_BIT * sizeof(T);

    // generate random integer in [0, N]
    auto generate_random_n(const T N) {
        U product = static_cast<U>(operator()() - RNG::min()) * N;
        T lsb = static_cast<T>(product);
        if (lsb < N) {
            T threshold = -static_cast<T>(N) % static_cast<T>(N);
            while (lsb < threshold) {
                product = static_cast<U>(operator()() - RNG::min()) * N;
                lsb = static_cast<T>(product);
            }
        }
        return static_cast<T>(product >> shift_size);
    }
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real> {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};

using RandomMersenne32 = Random<std::mt19937>;
using RandomLehmer32 = Random<lehmer<std::uint32_t>>;
using RandomWyhash32 = Random<wyhash<std::uint32_t>>;
using RandomMersenne64 = Random<std::mt19937_64>;
using RandomLehmer64 = Random<lehmer<std::uint64_t>>;
using RandomWyhash64 = Random<wyhash<std::uint64_t>>;

template <class T, class U, class F>
T pwr(T a, U n, F&& f, T base = 1) {
    while (n) {
        if (n & 1) base = f(base, a);
        if (n >>= 1) a = f(a, a);
    }
    return base;
}
// miller rabin
bool isPrime(u64 n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    u64 A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
    for (u64 a : A) {  // ^ count trailing zeroes
        u64 p = pwr(a % n, d, [&](u64 x, u64 y) { return x * y % n; }), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = u64(p) * p % n;
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}
// factor
u64 pollard(u64 n) {
    auto modmul = [](u64 x, u64 y, u64 n) {
        return x * y % n;
    };
    auto f = [=](u64 x) {
        return modmul(x, x, n) + 1;
    };
    u64 x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || std::gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, std::max(x, y) - std::min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return std::gcd(prd, n);
}
std::vector<u64> factor(u64 n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    u64 x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

std::vector<u64> distinct_prime_factors(u64 n) {
    auto f = factor(n);
    std::sort(f.begin(), f.end());
    f.erase(std::unique(f.begin(), f.end()), f.end());
    return f;
}

template <class T>
std::vector<i32> frequency(std::vector<T> a) {
    if (a.size() == 0) return std::vector<i32>{};
    std::sort(std::begin(a), std::end(a));
    std::vector<i32> ans{0};
    i32 n = static_cast<i32>(a.size());
    for (i32 i = 0; i != n; ++i)
        if (i == 0 || a[i] == a[i - 1])
            ans.back()++;
        else
            ans.push_back(1);
    return ans;
}

RandomWyhash32 rng;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(20) << std::fixed;
    i32 _tests = 1;
    // std::cin >> _tests;
    for (i32 _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        i32 n;
        std::cin >> n;
        std::vector<i32> a(n);
        for (auto& x : a) std::cin >> x;
        bool found = false;
        for (auto cnt : frequency(a))
            if (cnt > n - cnt) {
                std::cout << 3 << '\n';
                found = true;
                break;
            }
        if (found) continue;
        for (i32 trials = 100; trials >= 0; --trials) {
            if (found) break;
            i32 I = rng(n), J;
            do {
                J = rng(n);
            } while (a[J] == a[I]);
            auto num = std::abs(a[J] - a[I]);
            auto prime_fact = distinct_prime_factors(num);
            for (auto p : prime_fact) {
                if (p == 2) p = 4;
                if (found) break;
                std::vector<i32> b(n);
                for (i32 i = 0; i != n; ++i) b[i] = a[i] % p;
                for (auto cnt : frequency(b)) {
                    if (cnt > n - cnt) {
                        std::cout << p << '\n';
                        found = true;
                        break;
                    }
                }
            }
        }
        if (!found) {
            std::cout << -1 << '\n';
        }
    }
}