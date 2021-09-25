#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

using ll = int64_t;
using ld = long double;

struct IO {
    IO() = default;
    IO(const IO&) = delete;
    IO(IO&&) = delete;
    IO& operator=(const IO&) = delete;
    IO& operator=(IO&&) = delete;
    ~IO() {}

    template <class T, class D = void>
    struct is_default {
        static constexpr bool value = false;
    };
    template <class T>
    struct is_default<T,
                      std::void_t<decltype(std::cout << std::declval<T>())>> {
        static constexpr bool value = true;
    };
    template <class T, class D = void>
    struct is_iterable {
        static constexpr bool value = false;
    };
    template <class T>
    struct is_iterable<T,
                       std::void_t<decltype(std::begin(std::declval<T>()))>> {
        static constexpr bool value = true;
    };
    template <class T, class D = void, class E = void>
    struct is_applyable {
        static constexpr bool value = false;
    };
    template <class T>
    struct is_applyable<T, std::void_t<typename std::tuple_size<T>::type>,
                        std::void_t<decltype(std::get<0>(std::declval<T>()))>> {
        static constexpr bool value = true;
    };

    template <class T>
    struct needs_newline {
        static constexpr bool value =
            (is_iterable<T>::value or is_applyable<T>::value) and
            (not is_default<T>::value);
    };

    template <typename T, typename U>
    struct any_needs_newline {};
    template <typename T>
    struct any_needs_newline<T, std::index_sequence<>> {
        static constexpr bool value = false;
    };
    template <typename T, std::size_t I, std::size_t... Is>
    struct any_needs_newline<T, std::index_sequence<I, Is...>> {
        static constexpr bool value =
            (needs_newline<decltype(std::get<I>(std::declval<T>()))>::value) ||
            any_needs_newline<T, std::index_sequence<Is...>>::value;
    };

    template <typename T_>
    IO& operator<<(T_&& x) {
        using T = typename std::remove_cv<typename std::remove_reference<T_>::type>::type;
        static_assert(is_default<T>::value or is_iterable<T>::value or
                      is_applyable<T>::value);
        if constexpr (is_default<T>::value) {
            std::cout << x;
        } else if constexpr (is_iterable<T>::value) {
            // strings are immune
            using E = decltype(*std::begin(x));
            constexpr char sep = needs_newline<E>::value ? '\n' : ' ';
            int i = 0;
            for (const auto& y : x) {
                if (i++) std::cout << sep;
                operator<<(y);
            }
        } else if constexpr (is_applyable<T>::value) {
            // strings are immune
            constexpr char sep =
                (any_needs_newline<
                    T, std::make_index_sequence<std::tuple_size_v<T>>>::value)
                    ? '\n'
                    : ' ';
            int i = 0;
            std::apply(
                [this, &sep, &i](auto const&... y) {
                    ((std::cout << (i++ ? sep : '\0'), this->operator<<(y)),
                     ...);
                },
                x);
        }
        return *this;
    }
    template <typename T>
    IO& operator>>(T& x) {
        static_assert(is_default<T>::value or is_iterable<T>::value or
                      is_applyable<T>::value);
        if constexpr (is_default<T>::value)
            std::cin >> x;
        else if constexpr (is_iterable<T>::value)
            for (auto& y : x) operator>>(y);
        else if constexpr (is_applyable<T>::value)
            std::apply([this](auto const&... y) { ((operator>>(y)), ...); }, x);
        return *this;
    }

    IO* tie(std::nullptr_t) {
        std::cin.tie(nullptr);
        return this;
    }
    void sync_with_stdio(bool b) { std::cin.sync_with_stdio(b); }
};

IO io;
#define cin io
#define cout io


constexpr int mod = int(1e9) + 7;
constexpr int nttmod = 998'244'353;

template <std::uint32_t P>
struct ModInt32 {
   public:
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;
    using m32 = ModInt32;

   private:
    u32 v;
    static constexpr u32 get_r() {
        u32 iv = P;
        for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
        return -iv;
    }
    static constexpr u32 r = get_r(), r2 = -u64(P) % P;
    static_assert((P & 1) == 1);
    static_assert(-r * P == 1);
    static_assert(P < (1 << 30));
    static constexpr u32 pow_mod(u32 x, u64 y) {
        u32 res = 1;
        for (; y != 0; y >>= 1, x = u64(x) * x % P)
            if (y & 1) res = u64(res) * x % P;
        return res;
    }
    static constexpr u32 reduce(u64 x) {
        return (x + u64(u32(x) * r) * P) >> 32;
    }
    static constexpr u32 norm(u32 x) { return x - (P & -(x >= P)); }

   public:
    static constexpr u32 get_pr() {
        u32 tmp[32] = {}, cnt = 0;
        const u64 phi = P - 1;
        u64 m = phi;
        for (u64 i = 2; i * i <= m; ++i)
            if (m % i == 0) {
                tmp[cnt++] = i;
                while (m % i == 0) m /= i;
            }
        if (m != 1) tmp[cnt++] = m;
        for (u64 res = 2; res != P; ++res) {
            bool flag = true;
            for (u32 i = 0; i != cnt && flag; ++i)
                flag &= pow_mod(res, phi / tmp[i]) != 1;
            if (flag) return res;
        }
        return 0;
    }
    constexpr ModInt32() : v(0){};
    ~ModInt32() = default;
    constexpr ModInt32(u32 _v) : v(reduce(u64(_v) * r2)) {}
    constexpr ModInt32(i32 _v) : v(reduce(u64(_v % P + P) * r2)) {}
    constexpr ModInt32(u64 _v) : v(reduce((_v % P) * r2)) {}
    constexpr ModInt32(i64 _v) : v(reduce(u64(_v % P + P) * r2)) {}
    constexpr ModInt32(const m32& rhs) : v(rhs.v) {}
    constexpr u32 get() const { return norm(reduce(v)); }
    explicit constexpr operator u32() const { return get(); }
    explicit constexpr operator i32() const { return i32(get()); }
    constexpr m32& operator=(const m32& rhs) { return v = rhs.v, *this; }
    constexpr m32 operator-() const {
        m32 res;
        return res.v = (P << 1 & -(v != 0)) - v, res;
    }
    constexpr m32 inv() const { return pow(P - 2); }
    constexpr m32& operator+=(const m32& rhs) {
        return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
    }
    constexpr m32& operator-=(const m32& rhs) {
        return v -= rhs.v, v += P << 1 & -(v >> 31), *this;
    }
    constexpr m32& operator*=(const m32& rhs) {
        return v = reduce(u64(v) * rhs.v), *this;
    }
    constexpr m32& operator/=(const m32& rhs) {
        return this->operator*=(rhs.inv());
    }
    friend m32 operator+(const m32& lhs, const m32& rhs) {
        return m32(lhs) += rhs;
    }
    friend m32 operator-(const m32& lhs, const m32& rhs) {
        return m32(lhs) -= rhs;
    }
    friend m32 operator*(const m32& lhs, const m32& rhs) {
        return m32(lhs) *= rhs;
    }
    friend m32 operator/(const m32& lhs, const m32& rhs) {
        return m32(lhs) /= rhs;
    }
    friend bool operator==(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) == norm(rhs.v);
    }
    friend bool operator!=(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) != norm(rhs.v);
    }
    friend std::istream& operator>>(std::istream& is, m32& rhs) {
        return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
    }
    friend std::ostream& operator<<(std::ostream& os, const m32& rhs) {
        return os << rhs.get();
    }
    constexpr m32 pow(i64 y) const {
        // assumes P is a prime
        i64 rem = y % (P - 1);
        if (y > 0 && rem == 0)
            y = P - 1;
        else
            y = rem;
        m32 res(1), x(*this);
        for (; y != 0; y >>= 1, x *= x)
            if (y & 1) res *= x;
        return res;
    }
};

using mint = ModInt32<mod>;

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (ll _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(1 << n);
        vector p(n, vector<mint>(n));
        {
            vector<mint> s(n);
            cin >> s;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) p[i][j] = s[i] / (s[i] + s[j]);
        }
        vector<mint> scc_prob(1 << n, 1);
        vector win_against_mask_prob(1 << n, vector<mint>(n, 1));
        for (int i = 0; i < n; ++i) {
            for (int mask = 1; mask < (1 << n); ++mask) {
                int j = __lg(mask);
                win_against_mask_prob[mask][i] =
                    win_against_mask_prob[mask ^ (1 << j)][i] * p[i][j];
            }
        }
        mint ans = 0;
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i)
                if (mask >> i & 1)
                    for (int j = 0; j < n; ++j)
                        if (!(mask >> j & 1)) scc_prob[mask] *= p[i][j];
            int unmask = mask ^ ((1 << n) - 1);
            const auto& to_multiply = win_against_mask_prob[unmask];
            for (int submask = (mask - 1) & mask; submask;
                 (--submask) &= mask) {
                mint winprob = scc_prob[submask];
                for (int i = 0; i < n; ++i)
                    if ((mask >> i & 1) && !(submask >> i & 1))
                        winprob *= to_multiply[i];
                scc_prob[mask] -= winprob;
            }
            ans += scc_prob[mask] * __builtin_popcount(mask);
        }
        cout << ans << '\n';
    }
}

