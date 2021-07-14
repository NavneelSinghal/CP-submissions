#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;

using namespace std;

constexpr int mod = int(1e9) + 7;

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

const int N = 1e6;

vector<mint> fact(N + 1);
vector<mint> ifact(N + 1);
vector<mint> inv(N + 1);

void precompute_facts() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i;
    ifact[N] = 1 / fact[N];
    for (int i = N - 1; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);
    for (int i = 1; i <= N; ++i) inv[i] = fact[i - 1] * ifact[i];
}

mint C(int n, int r) {
    if (n < 0) return 0;
    if (r < 0 || r > n) return 0;
    return fact[n] * ifact[n - r] * ifact[r];
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    precompute_facts();
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, l, r;
        cin >> n >> l >> r;
        /* max f(a) = floor(n^2/4) - roughly half x, remaining -x */
        /*
         * first let n be even
         * d = x
         * 1 + e1, 2 + e2, ..., n + en
         * l <= 1 - x and n + x <= r -> all possible
         * i.e., x <= min(1 - l, r - n) -> each such x has answer
         * (n choose (n/2))
         *
         * for x to be possible:
         * 1..n/2 -> +x, n/2+1...n -> -x
         * n/2 - x >= l
         * n/2 + x <= r
         * x <= r - n/2
         * x <= n/2 - l
         */
        int w = min(1 - l, r - n);
        mint ans = w * C(n, n / 2);
        if (n & 1) ans *= 2;
        int force_plus = 0;
        int force_minus = n + 1;
        for (int i = 1; i <= n; ++i) {
            w++;
            while (force_plus - w + 1 < l) force_plus++;
            while (force_minus + w - 1 > r) force_minus--;
            // if (force_minus <= force_plus) break;
            if (n & 1) {
                for (int j = 0; j < 2; ++j) {
                    int remove_right = n - force_minus + 1;
                    int remove_left = force_plus;
                    int remaining_minus = n / 2 - remove_right + (j);
                    int remaining_plus =
                        n / 2 - remove_left + (j ^ 1);
                    ans += C(remaining_plus + remaining_minus, remaining_plus);
                }
            } else {
                int remove_right = n - force_minus + 1;
                int remove_left = force_plus;
                int remaining_minus = n / 2 - remove_right;
                int remaining_plus = n / 2 - remove_left;
                ans += C(remaining_plus + remaining_minus, remaining_plus);
            }
        }
        cout << ans << '\n';
    }
}