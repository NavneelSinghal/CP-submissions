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
        using value_type = ModInt32<P>;
        std::vector<value_type> res(std::max(x.size(), y.size()));
        for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i)
            res[i] = x[i] + y[i];
        if (x.size() < y.size())
            std::copy(y.begin() + x.size(), y.end(), res.begin() + x.size());
        else
            std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
        return norm(res);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> sub(const std::vector<ModInt32<P>>& x,
                                 const std::vector<ModInt32<P>>& y) {
        using i32 = std::int32_t;
        using value_type = ModInt32<P>;
        std::vector<value_type> res(std::max(x.size(), y.size()));
        for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i)
            res[i] = x[i] - y[i];
        if (x.size() < y.size())
            for (i32 i = x.size(), e = y.size(); i != e; ++i) res[i] = -y[i];
        else
            std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
        return norm(res);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul_xk(std::vector<ModInt32<P>> a, int k) {
        a.insert(a.begin(), k, 0);
        return a;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul_scalar(std::vector<ModInt32<P>> a,
                                        const ModInt32<P>& c) {
        for (auto& x : a) x *= c;
        return a;
    };
    template <std::uint32_t P>
    std::vector<ModInt32<P>> mul(std::vector<ModInt32<P>> x,
                                 std::vector<ModInt32<P>> y) {
        using i32 = std::int32_t;
        using value_type = ModInt32<P>;
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
        using value_type = ModInt32<P>;
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
    std::vector<ModInt32<P>> operator-(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return sub(x, y);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator*(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return mul(x, y);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator/(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return quorem(x, y);
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> operator%(const std::vector<ModInt32<P>>& x,
                                       const std::vector<ModInt32<P>>& y) {
        return rem(x, y);
    }
    template <std::uint32_t P>
    struct PolyMat {
       public:
        using poly = std::vector<ModInt32<P>>;
        /* a0 a1
           b0 b1 */
        poly a0, a1, b0, b1;
        PolyMat(const poly& a0, const poly& a1, const poly& b0, const poly& b1)
            : a0(a0), a1(a1), b0(b0), b1(b1) {}
        PolyMat(const PolyMat& rhs)
            : a0(rhs.a0), a1(rhs.a1), b0(rhs.b0), b1(rhs.b1) {}
        ~PolyMat() = default;
        bool is_identity_matrix() const {
            static constexpr ModInt32<P> ONE(1);
            return deg(a1) == -1 && deg(b0) == -1 && deg(a0) == 0 &&
                   a0[0] == ONE && deg(b1) == 0 && b1[0] == ONE;
        }
        PolyMat& operator=(const PolyMat& rhs) {
            return a0 = rhs.a0, a1 = rhs.a1, b0 = rhs.b0, b1 = rhs.b1, *this;
        }
    };
    template <std::uint32_t P>
    struct PolyVec {
       public:
        using poly = std::vector<ModInt32<P>>;
        /* a
           b */
        poly a, b;
        PolyVec(const poly& a, const poly& b) : a(a), b(b) {}
        PolyVec(const PolyVec& rhs) : a(rhs.a), b(rhs.b) {}
        ~PolyVec() = default;
        PolyVec& operator=(const PolyVec& rhs) {
            return a = rhs.a, b = rhs.b, *this;
        }
    };
    template <std::uint32_t P>
    PolyMat<P> operator*(const PolyMat<P>& lhs, const PolyMat<P>& rhs) {
        if (lhs.is_identity_matrix()) return rhs;
        if (rhs.is_identity_matrix()) return lhs;
        return PolyMat<P>(lhs.a0 * rhs.a0 + lhs.a1 * rhs.b0,
                          lhs.a0 * rhs.a1 + lhs.a1 * rhs.b1,
                          lhs.b0 * rhs.a0 + lhs.b1 * rhs.b0,
                          lhs.b0 * rhs.a1 + lhs.b1 * rhs.b1);
    }
    template <std::uint32_t P>
    PolyVec<P> operator*(const PolyMat<P>& lhs, const PolyVec<P>& rhs) {
        if (lhs.is_identity_matrix()) return rhs;
        return PolyVec<P>(lhs.a0 * rhs.a + lhs.a1 * rhs.b,
                          lhs.b0 * rhs.a + lhs.b1 * rhs.b);
    }
    template <std::uint32_t P>
    PolyMat<P> hgcd(const std::vector<ModInt32<P>>& p0,
                    const std::vector<ModInt32<P>>& p1) {
        using poly = std::vector<ModInt32<P>>;
        assert(deg(p0) > deg(p1));
        std::int32_t m = (deg(p0) - 1 >> 1) + 1, n = deg(p1);
        if (n < m) return PolyMat<P>({1}, {}, {}, {1});
        PolyMat<P> R(hgcd(poly(p0.begin() + m, p0.end()),
                          poly(p1.begin() + m, p1.end())));
        PolyVec<P> ab(R * PolyVec<P>(p0, p1));
        if (deg(ab.b) < m) return R;
        std::pair<poly, poly> qr(quo_with_rem(ab.a, ab.b));
        PolyMat<P> Q({}, {1}, {1}, -qr.first);
        std::int32_t k = (m << 1) - deg(ab.b);
        if (qr.second.size() <= k) return Q * R;
        return hgcd(poly(ab.b.begin() + k, ab.b.end()),
                    poly(qr.second.begin() + k, qr.second.end())) *
               Q * R;
    }
    template <std::uint32_t P>
    PolyMat<P> cogcd(const std::vector<ModInt32<P>>& p0,
                     const std::vector<ModInt32<P>>& p1) {
        using poly = std::vector<ModInt32<P>>;
        assert(deg(p0) > deg(p1));
        PolyMat<P> M(hgcd(p0, p1));
        PolyVec<P> p2p3(M * PolyVec<P>(p0, p1));
        if (deg(p2p3.b) == -1) return M;
        std::pair<poly, poly> qr(quo_with_rem(p2p3.a, p2p3.b));
        PolyMat<P> Q({}, {1}, {1}, -qr.first);
        if (deg(qr.second) == -1) return Q * M;
        return cogcd(p2p3.b, qr.second) * Q * M;
    }
    template <std::uint32_t P>
    std::vector<ModInt32<P>> exgcd(
        std::vector<ModInt32<P>> a, std::vector<ModInt32<P>> b,
        std::vector<ModInt32<P>>& x,
        std::vector<ModInt32<P>>& y) {  // ax + by = gcd(a, b)
        assert(deg(a) >= 0);
        assert(deg(b) >= 0);
        using poly = std::vector<ModInt32<P>>;
        PolyMat<P> c({}, {}, {}, {});
        if (deg(norm(a)) > deg(norm(b))) {
            c = cogcd(a, b);
        } else {
            std::pair<poly, poly> qr(quo_with_rem(a, b));
            c = cogcd(b, qr.second) * PolyMat<P>({}, {1}, {1}, -qr.first);
        }
        return a * (x = c.a0) + b * (y = c.a1);
    }
}  // namespace algebra

using mint = algebra::ModInt32<algebra::mod>;

/*

   to count this, first pick s positions (can be done in C(n - 1, s) ways)

   now we need to ensure that a non-chosen element is not equal to next element
   - 1

   so we use PIE:

   let's find the number of ways to get k ascents (or n - s - k - 1 descents),
   with at least i elements being equal to next element - 1

   contribution = (-1)^i * C(n - s - 1, i) * euler(n - s - i, n - s - k - 1)

   n -> n - s

   sum_{i = 0}^{k} (-1)^i C(n - 1, i) euler(n - i, n - k - 1)

   */

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

