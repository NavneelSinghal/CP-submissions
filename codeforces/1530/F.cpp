#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,bmi")

#include <bits/stdc++.h>

using namespace std;

constexpr int mod = 31607;

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
    static constexpr u32 reduce(u64 x) { return x + u64(u32(x) * r) * P >> 32; }
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
    constexpr ModInt32(u32 v) : v(reduce(u64(v) * r2)) {}
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
    friend std::istream& operator>>(std::istream& is, m32& rhs) {
        return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
    }
    friend std::ostream& operator<<(std::ostream& os, const m32& rhs) {
        return os << rhs.get();
    }
    constexpr m32 pow(i64 y) const {
        if ((y %= P - 1) < 0)
            y += P - 1;  // phi(P) = P - 1, assume P is a prime number
        m32 res(1), x(*this);
        for (; y != 0; y >>= 1, x *= x)
            if (y & 1) res *= x;
        return res;
    }
};

using mint = ModInt32<mod>;

template <bool inv = false>
void transform(mint a[], int n) {
    for (int len = 1, len2 = 2; len < n; len <<= 1, len2 <<= 1) {
        for (int i = 0; i < n; i += len2) {
            for (int j = i; j < i + len; ++j) {
                if constexpr (inv)
                    a[j] -= a[j + len];
                else
                    a[j] += a[j + len];
            }
        }
    }
}

#define trans(x) transform((x).data(), sz)
#define itrans(x) transform<true>((x).data(), sz)

void mul(vector<mint>& x, vector<mint>& y) {
    const int sz = x.size();
    for (int i = 0; i < sz; ++i) x[i] *= y[i];
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    mint inv = 1 / mint(10000);

    int n;
    cin >> n;
    const int sz = 1 << n;
    vector<vector<mint>> a(n, vector<mint>(n));
    for (auto& i : a)
        for (auto& j : i) {
            int t;
            cin >> t;
            j = t * inv;
        }

    const mint One = 1;
    const mint Zero = 0;

    vector<mint> x, x1, x2, x12;
    for (int j = 0; j < n; ++j) {
        vector<mint> ii(n);
        for (int i = 0; i < n; ++i) ii[i] = a[i][j] / (One - a[i][j]);
        vector<mint> y(sz), y1, y2, y12;
        y[0] = One;
        for (int i = 0; i < n; ++i) y[0] *= (One - a[i][j]);
        for (int i = 1; i < sz; ++i) {
            int l = __lg(i & -i);
            y[i] = y[i ^ 1 << l] * ii[l];
        }
        y[sz - 1] = 0;
        y1 = y2 = y12 = y;
        for (int i = 0; i < sz; ++i) {
            if (~i >> j & 1) y1[i] = Zero, y12[i] = Zero;
            if (~i >> (n - j - 1) & 1) y2[i] = Zero, y12[i] = Zero;
        }
        trans(y), trans(y1), trans(y2), trans(y12);
        if (j == 0)
            x.swap(y), x1.swap(y1), x2.swap(y2), x12.swap(y12);
        else
            mul(x, y), mul(x1, y1), mul(x2, y2), mul(x12, y12);
    }
    itrans(x), itrans(x1), itrans(x2), itrans(x12);
    mint ans = (x[0] - x1[0] - x2[0] + x12[0]);
    cout << (1 - ans).get() << "\n";

    return 0;
}
