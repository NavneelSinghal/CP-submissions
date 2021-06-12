#ifndef LOCAL
    #pragma GCC optimize("O3")
    #pragma GCC optimize("unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#endif

#ifdef DEBUG
    #include "debug/bits/stdc++.h"
    #include "debug/ext/pb_ds/assoc_container.hpp"
    #include "debug/ext/pb_ds/tree_policy.hpp"
#else
    #include "bits/stdc++.h"
    #include "ext/pb_ds/assoc_container.hpp"
    #include "ext/pb_ds/tree_policy.hpp"
#endif
// #include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
// using namespace __gnu_cxx;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#ifdef DEBUG
    #include "debug/debug.hpp"
#else
    #define debug(...) 0
#endif
#ifdef TIMING
    #include "debug/timing.hpp"
#else
// clang-format off
struct Stopwatch { Stopwatch(const string &s = "") {} void reset(){}
    void pause(){} void play(){} void print(){} ll elapsed() { return 0; }; };
// clang-format on
#endif

constexpr int inf = int(1e9);
constexpr ll linf = ll(3e18L);
constexpr ld eps = 1e-9;
const ld pi = acosl(-1.0);

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

void setIO(string name = "") {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    cout << setprecision(20) << fixed;
    if (name.size() == 0) return;
    ignore = freopen((name + ".in").c_str(), "r", stdin);
    ignore = freopen((name + ".out").c_str(), "w", stdout);
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int mod = int(1e9) + 7;
constexpr int nttmod = 998'244'353;

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
    friend M operator++(M& a, int) { return exchange(a, ++M(a)); }
    friend M operator--(M& a, int) { return exchange(a, --M(a)); }
    friend M operator+(M a) { return a; }
    friend M operator-(M a) { return a.v_ = a.v_ ? Modulus - a.v_ : 0, a; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a /= b; }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    friend istream& operator>>(istream& is, M& x) {
        int64_t v;
        return is >> v, x = v, is;
    }
    friend ostream& operator<<(ostream& os, M x) { return os << x.v_; }
    friend bool operator==(M a, M b) { return a.v_ == b.v_; }
    friend bool operator!=(M a, M b) { return a.v_ != b.v_; }

   private:
    static pair<int, int> extgcd(int a, int b) {
        array<int, 2> x{1, 0};
        while (b) swap(x[0] -= a / b * x[1], x[1]), swap(a %= b, b);
        return {x[0], a};
    }
    uint32_t v_;
};

using mint = Modular<mod>;

// when using integers, keep overflow in mind
template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    // assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}

auto main() -> signed {
#ifdef CUSTOM_IO
    IO::IOinit();
#else
    setIO();
#endif

    int TESTS = 1;
    // cin >> TESTS;

    auto precompute = [&]() -> void {
    };

    auto solve = [&](int) -> void {
        Stopwatch stopwatch;
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        sort(begin(a), end(a));
        vector<double> pre(n + 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + a[i - 1];
        }
        double ans = 1e18;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, pre[n] / n - pre[i + 1] / n + a[i] / 2.0 - a[i] * 1.0 * (n - i - 1) / n);
        }
        ans = min(ans, pre[n] / n);
        cout << ans << '\n';
    };

    auto brute = [&]() -> void {
    };

    ignore = brute;
    precompute();
    for (int _t = 1; _t <= TESTS; ++_t) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute();
    }
    return 0;
}