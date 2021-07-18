#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,bmi")

#include <bits/stdc++.h>

constexpr int mod = 31607;

template <uint32_t Modulus>
class Modular {
    using M = Modular;

   public:
    static_assert(int(Modulus) >= 1, "Modulus must be in the range [1, 2^31)");
    static constexpr int modulus() { return Modulus; }
    static M raw(uint32_t v) { return *reinterpret_cast<M*>(&v); }
    Modular() : v_(0) {}
    Modular(int64_t v) : v_((v %= Modulus) < 0 ? v + Modulus : v) {}
    template <class T>
    explicit operator T() const {
        return v_;
    }
    M& operator++() { return v_ = ++v_ == Modulus ? 0 : v_, *this; }
    M& operator--() { return --(v_ ? v_ : v_ = Modulus), *this; }
    M& operator*=(M o) { return v_ = uint64_t(v_) * o.v_ % Modulus, *this; }
    M& operator/=(M o) {
        auto [inv, gcd] = extgcd(o.v_, Modulus);
        assert(gcd == 1);
        return *this *= inv;
    }
    M& operator+=(M o) {
        return v_ = int(v_ += o.v_ - Modulus) < 0 ? v_ + Modulus : v_, *this;
    }
    M& operator-=(M o) {
        return v_ = int(v_ -= o.v_) < 0 ? v_ + Modulus : v_, *this;
    }
    friend M operator++(M& a, int) { return std::exchange(a, ++M(a)); }
    friend M operator--(M& a, int) { return std::exchange(a, --M(a)); }
    friend M operator+(M a) { return a; }
    friend M operator-(M a) { return a.v_ = a.v_ ? Modulus - a.v_ : 0, a; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a /= b; }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    template <class T>
    friend T& operator>>(T& is, M& x) {
        int64_t v;
        return is >> v, x = v, is;
    }
    template <class T>
    friend T& operator<<(T& os, M x) {
        return os << x.v_;
    }
    friend bool operator==(M a, M b) { return a.v_ == b.v_; }
    friend bool operator!=(M a, M b) { return a.v_ != b.v_; }

   private:
    static std::pair<int, int> extgcd(int a, int b) {
        std::array<int, 2> x{1, 0};
        while (b) std::swap(x[0] -= a / b * x[1], x[1]), std::swap(a %= b, b);
        return {x[0], a};
    }
    uint32_t v_;
};

using mint = Modular<mod>;

using namespace std;

template <bool inv = false>
void transform(mint a[], int n) {
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
#pragma GCC ivdep
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
    cin.tie(nullptr)->sync_with_stdio(false);

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
    cout << int(1 - ans) << "\n";

    return 0;
}
