#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

struct IOPre {
    static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;
    std::array<char, 4 * SZ> num;
    constexpr IOPre() : num{} {
        for (int i = 0; i < SZ; i++) {
            int n = i;
            for (int j = 3; j >= 0; j--) {
                num[i * 4 + j] = static_cast<char>(n % TEN + '0');
                n /= TEN;
            }
        }
    }
};
struct IO {
#if !HAVE_DECL_FREAD_UNLOCKED
    #define fread_unlocked fread
#endif
#if !HAVE_DECL_FWRITE_UNLOCKED
    #define fwrite_unlocked fwrite
#endif
    static constexpr int SZ = 1 << 17, LEN = 32, TEN = 10, HUNDRED = TEN * TEN,
                         THOUSAND = HUNDRED * TEN, TENTHOUSAND = THOUSAND * TEN,
                         MAGIC_MULTIPLY = 205, MAGIC_SHIFT = 11, MASK = 15,
                         TWELVE = 12, SIXTEEN = 16;
    static constexpr IOPre io_pre = {};
    std::array<char, SZ> input_buffer, output_buffer;
    int input_ptr_left, input_ptr_right, output_ptr_right;

    IO()
        : input_buffer{},
          output_buffer{},
          input_ptr_left{},
          input_ptr_right{},
          output_ptr_right{} {}
    IO(const IO&) = delete;
    IO(IO&&) = delete;
    IO& operator=(const IO&) = delete;
    IO& operator=(IO&&) = delete;

    ~IO() { flush(); }

    template <class T>
    struct is_char {
        static constexpr bool value = std::is_same_v<T, char>;
    };

    template <class T>
    struct is_bool {
        static constexpr bool value = std::is_same_v<T, bool>;
    };

    template <class T>
    struct is_string {
        static constexpr bool value =
            std::is_same_v<T, std::string> || std::is_same_v<T, const char*> ||
            std::is_same_v<T, char*> || std::is_same_v<std::decay_t<T>, char*>;
    };

    template <class T, class D = void>
    struct is_custom {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_custom<T, std::void_t<typename T::internal_value_type>> {
        static constexpr bool value = true;
    };

    template <class T>
    struct is_default {
        static constexpr bool value = is_char<T>::value || is_bool<T>::value ||
                                      is_string<T>::value ||
                                      std::is_integral_v<T>;
    };

    template <class T, class D = void>
    struct is_iterable {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_iterable<
        T, typename std::void_t<decltype(std::begin(std::declval<T>()))>> {
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
    static constexpr bool needs_newline = (is_iterable<T>::value ||
                                           is_applyable<T>::value) &&
                                          (!is_default<T>::value);

    template <typename T, typename U>
    struct any_needs_newline {
        static constexpr bool value = false;
    };
    template <typename T>
    struct any_needs_newline<T, std::index_sequence<>> {
        static constexpr bool value = false;
    };
    template <typename T, std::size_t I, std::size_t... Is>
    struct any_needs_newline<T, std::index_sequence<I, Is...>> {
        static constexpr bool value =
            needs_newline<decltype(std::get<I>(std::declval<T>()))> ||
            any_needs_newline<T, std::index_sequence<Is...>>::value;
    };

    inline void load() {
        memmove(std::begin(input_buffer),
                std::begin(input_buffer) + input_ptr_left,
                input_ptr_right - input_ptr_left);
        input_ptr_right =
            input_ptr_right - input_ptr_left +
            static_cast<int>(fread_unlocked(
                std::begin(input_buffer) + input_ptr_right - input_ptr_left, 1,
                SZ - input_ptr_right + input_ptr_left, stdin));
        input_ptr_left = 0;
    }

    inline void read_char(char& c) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        c = input_buffer[input_ptr_left++];
    }
    inline void read_string(std::string& x) {
        char c;
        while (read_char(c), c < '!') continue;
        x = c;
        while (read_char(c), c >= '!') x += c;
    }
    template <class T>
    inline std::enable_if_t<std::is_integral_v<T>, void> read_int(T& x) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        char c = 0;
        do c = input_buffer[input_ptr_left++];
        while (c < '-');
        [[maybe_unused]] bool minus = false;
        if constexpr (std::is_signed<T>::value == true)
            if (c == '-') minus = true, c = input_buffer[input_ptr_left++];
        x = 0;
        while (c >= '0')
            x = x * TEN + (c & MASK), c = input_buffer[input_ptr_left++];
        if constexpr (std::is_signed<T>::value == true)
            if (minus) x = -x;
    }

    inline void skip_space() {
        if (input_ptr_left + LEN > input_ptr_right) load();
        while (input_buffer[input_ptr_left] <= ' ') input_ptr_left++;
    }

    inline void flush() {
        fwrite_unlocked(std::begin(output_buffer), 1, output_ptr_right, stdout);
        output_ptr_right = 0;
    }

    inline void write_char(char c) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = c;
    }

    inline void write_bool(bool b) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = b ? '1' : '0';
    }

    inline void write_string(const std::string& s) {
        for (auto x : s) write_char(x);
    }

    inline void write_string(const char* s) {
        while (*s) write_char(*s++);
    }

    inline void write_string(char* s) {
        while (*s) write_char(*s++);
    }

    template <typename T>
    inline std::enable_if_t<std::is_integral_v<T>, void> write_int(T x) {
        if (output_ptr_right > SZ - LEN) flush();
        if (!x) {
            output_buffer[output_ptr_right++] = '0';
            return;
        }
        if constexpr (std::is_signed<T>::value == true)
            if (x < 0) output_buffer[output_ptr_right++] = '-', x = -x;
        int i = TWELVE;
        std::array<char, SIXTEEN> buf{};
        while (x >= TENTHOUSAND) {
            memcpy(std::begin(buf) + i,
                   std::begin(io_pre.num) + (x % TENTHOUSAND) * 4, 4);
            x /= TENTHOUSAND;
            i -= 4;
        }
        if (x < HUNDRED) {
            if (x < TEN) {
                output_buffer[output_ptr_right++] = static_cast<char>('0' + x);
            } else {
                std::uint32_t q =
                    (static_cast<std::uint32_t>(x) * MAGIC_MULTIPLY) >>
                    MAGIC_SHIFT;
                std::uint32_t r = static_cast<std::uint32_t>(x) - q * TEN;
                output_buffer[output_ptr_right] = static_cast<char>('0' + q);
                output_buffer[output_ptr_right + 1] =
                    static_cast<char>('0' + r);
                output_ptr_right += 2;
            }
        } else {
            if (x < THOUSAND) {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2) + 1, 3),
                    output_ptr_right += 3;
            } else {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2), 4),
                    output_ptr_right += 4;
            }
        }
        memcpy(std::begin(output_buffer) + output_ptr_right,
               std::begin(buf) + i + 4, TWELVE - i);
        output_ptr_right += TWELVE - i;
    }
    template <typename T_>
    IO& operator<<(T_&& x) {
        using T = typename std::remove_cv<
            typename std::remove_reference<T_>::type>::type;
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        if constexpr (is_custom<T>::value) {
            write_int(x.get());
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_bool<T>::value) {
                write_bool(x);
            } else if constexpr (is_string<T>::value) {
                write_string(x);
            } else if constexpr (is_char<T>::value) {
                write_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                write_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            // strings are immune
            using E = decltype(*std::begin(x));
            constexpr char sep = needs_newline<E> ? '\n' : ' ';
            int i = 0;
            for (const auto& y : x) {
                if (i++) write_char(sep);
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
                    (((i++ ? write_char(sep) : void()), this->operator<<(y)),
                     ...);
                },
                x);
        }
        return *this;
    }
    template <typename T>
    IO& operator>>(T& x) {
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        static_assert(!is_bool<T>::value);
        if constexpr (is_custom<T>::value) {
            typename T::internal_value_type y;
            read_int(y);
            x = y;
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_string<T>::value) {
                read_string(x);
            } else if constexpr (is_char<T>::value) {
                read_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                read_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            for (auto& y : x) operator>>(y);
        } else if constexpr (is_applyable<T>::value) {
            std::apply([this](auto&... y) { ((this->operator>>(y)), ...); }, x);
        }
        return *this;
    }

    IO* tie(std::nullptr_t) { return this; }
    void sync_with_stdio(bool) {}
};
IO io;
#define cin io
#define cout io

namespace algebra {

    // source: modified from https://github.com/ei1333/library

    template <std::uint32_t P>
    struct ModInt32 {
       public:
        using i32 = std::int32_t;
        using u32 = std::uint32_t;
        using i64 = std::int64_t;
        using u64 = std::uint64_t;
        using m32 = ModInt32;
        using internal_value_type = u32;

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
                    tmp[cnt++] = u32(i);
                    while (m % i == 0) m /= i;
                }
            if (m != 1) tmp[cnt++] = u32(m);
            for (u64 res = 2; res != P; ++res) {
                bool flag = true;
                for (u32 i = 0; i != cnt && flag; ++i)
                    flag &= pow_mod(res, phi / tmp[i]) != 1;
                if (flag) return u32(res);
            }
            return 0;
        }
        constexpr ModInt32() : v(0){};
        ~ModInt32() = default;
        constexpr ModInt32(u32 _v) : v(reduce(u64(_v) * r2)) {}
        constexpr ModInt32(i32 _v)
            : v(reduce(u64(_v % i64(P) + i64(P)) * r2)) {}
        constexpr ModInt32(u64 _v) : v(reduce((_v % P) * r2)) {}
        constexpr ModInt32(i64 _v)
            : v(reduce(u64(_v % i64(P) + i64(P)) * r2)) {}
        constexpr ModInt32(const m32& rhs) : v(rhs.v) {}
        constexpr u32 get() const { return norm(reduce(v)); }
        explicit constexpr operator u32() const { return get(); }
        explicit constexpr operator i32() const { return i32(get()); }
        constexpr m32& operator=(const m32& rhs) { return v = rhs.v, *this; }
        constexpr m32 operator-() const {
            m32 res;
            return res.v = (P << 1 & -(v != 0)) - v, res;
        }
        constexpr m32 inv() const { return pow(-1); }
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
        template <class T>
        friend T& operator>>(T& is, m32& rhs) {
            return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
        }
        template <class T>
        friend T& operator<<(T& os, const m32& rhs) {
            return os << rhs.get();
        }
        constexpr m32 pow(i64 y) const {
            i64 rem = y % (P - 1);
            if (y > 0 && rem == 0)
                y = P - 1;
            else
                y = rem;
            if (y < 0) y += P - 1;
            m32 res(1), x(*this);
            for (; y != 0; y >>= 1, x *= x)
                if (y & 1) res *= x;
            return res;
        }
    };

    // optimization to reduce used space
    template <std::uint32_t N, std::uint32_t P>
    struct Combi {
        using mint = ModInt32<P>;
        std::array<mint, N> fact, ifact, inv;
        Combi() {
            fact[0] = 1;
            for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i;
            ifact[N] = 1 / fact[N];
            for (int i = N - 1; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);
            for (int i = 1; i <= N; ++i) inv[i] = fact[i - 1] * ifact[i];
        }
        mint C(int n, int r) {
            if (r < 0 || r > n) return 0;
            return fact[n] * ifact[n - r] * ifact[r];
        }
    };
    constexpr int mod = 998'244'353;
    Combi<1 << 21, mod> combi;

    std::uint64_t get_len(std::uint64_t n) {  // if n=0, boom
        return --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8,
               n |= n >> 16, n |= n >> 32, ++n;
    }
    template <std::uint32_t P>
    struct NTT {
       public:
        using i32 = std::int32_t;
        using u32 = std::uint32_t;
        using i64 = std::int64_t;
        using u64 = std::uint64_t;
        using value_type = ModInt32<P>;

       private:
        static inline value_type ROOT[1 << 20], IROOT[1 << 20];

       public:
        NTT() = delete;
        static void idft(i32 n, value_type x[]) {
            for (i32 i = 2; i < n; i <<= 1) {
                for (i32 j = 0, l = i >> 1; j != l; ++j) {
                    value_type u = x[j], v = x[j + l];
                    x[j] = u + v, x[j + l] = u - v;
                }
                for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                    value_type root = IROOT[m];
                    for (i32 k = 0; k != l; ++k) {
                        value_type u = x[j + k], v = x[j + k + l];
                        x[j + k] = u + v, x[j + k + l] = (u - v) * root;
                    }
                }
            }
            value_type iv(P - (P - 1) / n);
            for (i32 j = 0, l = n >> 1; j != l; ++j) {
                value_type u = x[j] * iv, v = x[j + l] * iv;
                x[j] = u + v, x[j + l] = u - v;
            }
        }
        static void dft(i32 n, value_type x[]) {
            static i32 lim = 0;
            static constexpr u32 pr = value_type::get_pr();
            static_assert(pr != 0);
            static constexpr value_type G(pr);
            if (lim == 0) {
                ROOT[1 << 19] = G.pow((P - 1) >> 21),
                          IROOT[1 << 19] = G.pow(P - 1 - i32((P - 1) >> 21));
                for (i32 i = 18; i != -1; --i)
                    ROOT[1 << i] = ROOT[1 << (i + 1)] * ROOT[1 << (i + 1)],
                              IROOT[1 << i] =
                                  IROOT[1 << (i + 1)] * IROOT[1 << (i + 1)];
                lim = 1;
            }
            while ((lim << 1) < n) {
                for (i32 i = lim + 1, e = lim << 1; i < e; ++i)
                    ROOT[i] = ROOT[i - lim] * ROOT[lim],
                    IROOT[i] = IROOT[i - lim] * IROOT[lim];
                lim <<= 1;
            }
            for (i32 j = 0, l = n >> 1; j != l; ++j) {
                value_type u = x[j], v = x[j + l];
                x[j] = u + v, x[j + l] = u - v;
            }
            for (i32 i = n >> 1; i >= 2; i >>= 1) {
                for (i32 j = 0, l = i >> 1; j != l; ++j) {
                    value_type u = x[j], v = x[j + l];
                    x[j] = u + v, x[j + l] = u - v;
                }
                for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                    value_type root = ROOT[m];
                    for (i32 k = 0; k != l; ++k) {
                        value_type u = x[j + k], v = x[j + k + l] * root;
                        x[j + k] = u + v, x[j + k + l] = u - v;
                    }
                }
            }
        }
    };

    // optimization to reduce used space
    using value_type = ModInt32<mod>;
    static value_type a[1 << 21], b[1 << 21];

    template <std::uint32_t P>
    void dft(std::uint32_t n, ModInt32<P> x[]) {
        NTT<P>::dft(n, x);
    }
    template <std::uint32_t P>
    void idft(std::uint32_t n, ModInt32<P> x[]) {
        NTT<P>::idft(n, x);
    }
    template <std::uint32_t P>
    std::int32_t deg(const std::vector<ModInt32<P>>& x) {
        // return -1 if x is 0
        std::int32_t n = std::int32_t(x.size()) - 1;
        static constexpr ModInt32<P> ZERO(0);
        while (n >= 0 && x[n] == ZERO) --n;
        return n;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>>& norm(std::vector<ModInt32<P>>& x) {
        return x.resize(std::max(deg(x) + 1, 1)), x;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> norm(std::vector<ModInt32<P>>&& x) {
        return x.resize(std::max(deg(x) + 1, 1)), x;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> add(const std::vector<ModInt32<P>>& x,
                                 const std::vector<ModInt32<P>>& y) {
        using i32 = std::int32_t;
        std::vector<value_type> res(std::max(x.size(), y.size()));
        for (i32 i = 0, e = (i32)std::min(x.size(), y.size()); i != e; ++i)
            res[i] = x[i] + y[i];
        if (x.size() < y.size())
            std::copy(y.begin() + x.size(), y.end(), res.begin() + x.size());
        else
            std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
        return norm(res);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul_xk(std::vector<ModInt32<P>> p, int k) {
        p.insert(p.begin(), k, 0);
        return p;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul_scalar(std::vector<ModInt32<P>> p,
                                        const ModInt32<P>& c) {
        for (auto& x : p) x *= c;
        return p;
    };
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul(std::vector<ModInt32<P>> x,
                                 std::vector<ModInt32<P>> y) {
        using i32 = std::int32_t;
        norm(x), norm(y);
        if (deg(x) == -1 || deg(y) == -1) return {0};
        std::vector<value_type> res(x.size() + y.size() - 1);
        if (std::min(x.size(), y.size()) <= 8) {
            i32 n = (i32)x.size(), m = (i32)y.size();
            std::fill(res.begin(), res.end(), 0);
            for (i32 i = 0; i != n; ++i)
                for (i32 j = 0; j != m; ++j) res[i + j] += x[i] * y[j];
        } else {
            std::copy(x.begin(), x.end(), a);
            std::copy(y.begin(), y.end(), b);
            i32 old_size = (i32)res.size(), len = (i32)get_len(old_size);
            std::fill(a + x.size(), a + len, 0);
            std::fill(b + y.size(), b + len, 0);
            dft(len, a), dft(len, b);
            res.resize(len);
            for (i32 i = 0; i != len; ++i) res[i] = a[i] * b[i];
            idft(len, res.data());
            res.resize(old_size);
        }
        return res;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> taylor_shift(const std::vector<ModInt32<P>>& x,
                                          const ModInt32<P>& c) {
        if (deg(x) < 1) return x;
        using i32 = std::int32_t;
        i32 n = (i32)x.size(), len = (i32)get_len((n << 1) - 1);
        for (i32 i = 0; i != n; ++i) a[n - i - 1] = x[i] * combi.fact[i];
        value_type k(c);
        b[0] = 1;
        for (i32 i = 1; i != n; ++i) b[i] = k * combi.ifact[i], k *= c;
        std::fill(a + n, a + len, 0), std::fill(b + n, b + len, 0);
        dft(len, a), dft(len, b);
        for (i32 i = 0; i != len; ++i) a[i] *= b[i];
        idft(len, a);
        std::vector<value_type> res(n);
        std::reverse_copy(a, a + n, res.begin());
        for (i32 i = 2; i != n; ++i) res[i] *= combi.ifact[i];
        return res;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator-(const std::vector<ModInt32<P>>& x) {
        using i32 = std::int32_t;
        i32 n = x.size();
        std::vector<ModInt32<P>> res(n);
        for (i32 i = 0; i != n; ++i) res[i] = -x[i];
        return res;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator+(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return add(x, y);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator*(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return mul(x, y);
    }
}  // namespace algebra

using mint = algebra::ModInt32<algebra::mod>;

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, s;
        cin >> n >> s;
        auto stirling = [&](int n) -> vector<mint> {
            vector<mint> a(n + 1), b(n + 1), c(n + 1);
            for (int i = 0; i <= n; ++i)
                a[i] = mint(i).pow(n) * algebra::combi.ifact[i];
            for (int i = 0; i <= n; ++i)
                b[i] = (i & 1 ? -algebra::combi.ifact[i]
                              : algebra::combi.ifact[i]);
            auto p = a * b;
            for (int i = 0; i <= n; ++i) c[i] = p[i] * algebra::combi.fact[i];
            return c;
        };
        n -= s;
        vector<array<vector<mint>, 2>> t(4 * n);
        auto rec = [&](auto self, int v, int l, int r) -> void {
            if (l + 1 == r) {
                vector p{-l * algebra::combi.inv[r], -algebra::combi.inv[r]};
                t[v] = {p, p};
            } else {
                int m = l + (r - l) / 2;
                self(self, 2 * v, l, m);
                self(self, 2 * v + 1, m, r);
                t[v] = {t[2 * v][0] * t[2 * v + 1][0],
                        t[2 * v][0] * t[2 * v + 1][1] +
                            algebra::mul_xk(t[2 * v][1], r - m)};
            }
        };
        rec(rec, 1, 0, n);
        auto work = [&](vector<mint> a) -> vector<mint> {
            int sz = (int)a.size();
            a.resize(n + 1);
            auto rec = [&](auto self, int v, int l,
                           int r) -> array<vector<mint>, 2> {
                if (l + 1 == r) {
                    return array{algebra::mul_scalar(t[v][0], a[r]),
                                 algebra::mul_xk(vector{a[r]}, 1)};
                } else {
                    int m = l + (r - l) / 2;
                    auto [p1_l, p2_l] = self(self, 2 * v, l, m);
                    auto [p1_r, p2_r] = self(self, 2 * v + 1, m, r);
                    return array{p1_l + t[2 * v][0] * p1_r + t[2 * v][1] * p2_r,
                                 p2_l + algebra::mul_xk(p2_r, m - l)};
                }
            };
            auto [p1, p2] = rec(rec, 1, 0, n);
            auto ans = p1 + p2;
            ans[0] += a[0];
            ans.resize(sz);
            reverse(begin(ans), end(ans));
            ans = algebra::taylor_shift(ans, -mint(1));
            reverse(begin(ans), end(ans));
            return ans;
        };
        auto S = work(stirling(n)) + work(stirling(n - 1));
        for (int i = 0; i < s; ++i) cout << 0 << ' ';
        auto factor = algebra::combi.C(n + s - 1, s);
        reverse(begin(S), end(S));
        for (int i = s; i < n + s; ++i) cout << S[i - s] * factor << ' ';
        cout << '\n';
    }
}

