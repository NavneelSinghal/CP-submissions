// clang-format off

#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")
/* optimizing pragmas end */

// #include <string>
// #include <bits/cxxabi_forced.h>
// #include <bits/functexcept.h>
// #include <bits/functional_hash.h>
// #include <iosfwd>
// #pragma push_macro("__SIZEOF_LONG__")
// #pragma push_macro("__cplusplus")
// #define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
// #define unsigned unsigned long
// #define __cplusplus 201102L
// #define __builtin_popcountl __builtin_popcountll
// #define __builtin_ctzl __builtin_ctzll
// #include <bitset>
// #pragma pop_macro("__cplusplus")
// #pragma pop_macro("__SIZEOF_LONG__")
// #undef unsigned
// #undef __builtin_popcountl
// #undef __builtin_ctzl
/* 64-bit bitset ends */

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
// #include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
// using namespace __gnu_cxx;

#define int int_fast32_t
#define ll int_fast64_t
#define unordered_map gp_hash_table

template <typename T>
void ignore_unused(const T &) {}

#ifdef DEBUG
#define debug(args...)                               \
    {                                                \
        std::string _s = #args;                      \
        replace(_s.begin(), _s.end(), ',', ' ');     \
        std::stringstream _ss(_s);                   \
        std::istream_iterator<std::string> _it(_ss); \
        err(_it, args);                              \
    }
#define print_container(v)          \
    {                               \
        bool first = true;          \
        os << "[";                  \
        for (auto x : v) {          \
            if (!first) os << ", "; \
            os << x;                \
            first = false;          \
        }                           \
        return os << "]";           \
    }
void err(std::istream_iterator<std::string> it) { ignore_unused(it); }
template <typename T, typename... Args>
void err(std::istream_iterator<std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}
// clang-format off
template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) { return os << "(" << p.first << "," << p.second << ")"; }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::vector<T>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::set<T>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::map<T1, T2>& v) { print_container(v); }
template <typename T1, typename T2, class C> inline std::ostream &operator << (std::ostream & os, const unordered_map<T1, T2, C>& v) { print_container(v); }
template <typename T, class C> inline std::ostream &operator << (std::ostream & os, const unordered_set<T, C>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::multimap<T1, T2>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::multiset<T>& v) { print_container(v); }
#else
#define debug(args...) 0
#endif

template <typename X, typename Y> X &remin(X &x, const Y &y) { return x = (y < x) ? y : x; }
template <typename X, typename Y> X &remax(X &x, const Y &y) { return x = (x < y) ? y : x; }
template <typename X, typename Y> [[nodiscard]] bool ckmin(X &x, const Y &y) { return (y < x) ? (x = y, 1) : 0; }
template <typename X, typename Y> [[nodiscard]] bool ckmax(X &x, const Y &y) { return (x < y) ? (x = y, 1) : 0; }
template <typename T> inline T sq(T a) { return a * a; }
template <typename T> inline T sq_dist(pair<T, T> &a, pair<T, T> &b) { return sq(a.first - b.first) + sq(a.second - b.second); }
template <typename T> inline long double dist(pair<T, T> &a, pair<T, T> &b) { return sqrtl(sq_dist(a, b)); }
inline long long isqrt(long long n) {
    long long sq = (long long)sqrtl((long double)n) - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) sq++;
    if ((sq * sq) == n) return sq;
    return sq - 1;
}
inline bool is_sq(int n) { int w = (int)isqrt(n); return w * w == n; }

struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
struct pair_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<int, int> p) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(p.first * 31 + p.second + FIXED_RANDOM);
    }
};

template <class Fun>
class y_combinator_result {
    Fun fun_;
   public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}
    template <class... Args>
    decltype(auto) operator()(Args &&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(20) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin); ignore_unused(fout);
}

// clang-format on

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;
const long double pi = acosl(-1.0);
constexpr long double eps = 1e-9;

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n, int mod = ::mod) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
[[nodiscard]] T pwr(T a, int64_t n) {
    T ans(1);
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

template <int32_t MOD = 998'244'353>
struct Modular {
    int32_t value;
    static const int32_t MOD_value = MOD;

    Modular(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }
    Modular(long long a, long long b) : value(0) {
        *this += a;
        *this /= b;
    }

    Modular &operator+=(Modular const &b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    Modular &operator-=(Modular const &b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }
    Modular &operator*=(Modular const &b) {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend Modular mexp(Modular a, long long e) {
        Modular res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

    Modular &operator/=(Modular const &b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &os, Modular const &a) {
        return os << a.value;
    }
    friend bool operator==(Modular const &a, Modular const &b) {
        return a.value == b.value;
    }
    friend bool operator!=(Modular const &a, Modular const &b) {
        return a.value != b.value;
    }
};

using mint = Modular<mod>;

const int inf = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 2e5 + 5;

void precompute() {}

template <typename node = pair<ll, ll>, typename T = ll>
struct SegTree {

    // change this
    node combine(node n1, node n2) { return min(n1, n2); }
    node make_node(T val, int t) { return make_pair(ll(val), ll(t)); }
    
    const node ID = {ll(2e9), ll(-1)};
    vector<node> t;
    int n;

    SegTree(vector<T>& a) {
        this->n = a.size();
        this->t.resize(4 * a.size() + 4);
        _build(1, 0, n - 1, a);
    }

    void update(int i, T val) { _update(1, 0, n - 1, i, val); }
    node query(int l, int r) { return _query(1, 0, n - 1, l, r); }

    void _build(int v, int l, int r, vector<T>& a) {
        if (l == r) {
            t[v] = make_node(a[l], l);
            return;
        }
        int mid = (l + r) >> 1;
        _build(v << 1, l, mid, a);
        _build((v << 1) | 1, mid + 1, r, a);
        t[v] = combine(t[(v << 1)], t[(v << 1) | 1]);
    }

    void _update(int v, int l, int r, int idx, T val) {
        if (l == r) {
            t[v] = make_node(val, idx);
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid)
            _update(v << 1, l, mid, idx, val);
        else
            _update((v << 1) | 1, mid + 1, r, idx, val);
        t[v] = combine(t[v << 1], t[(v << 1) | 1]);
    }

    node _query(int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) >> 1;
        if (l > tm) return _query((v << 1) | 1, tm + 1, tr, l, r);
        if (tm + 1 > r) return _query(v << 1, tl, tm, l, r);
        return combine(_query(v << 1, tl, tm, l, tm),
                       _query((v << 1) | 1, tm + 1, tr, tm + 1, r));
    }
};



void solve(int) {
    ll n, p;
    cin >> n >> p;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    SegTree s(a);

    function<ll(ll, ll)> rec = [&](ll l, ll r) {
        
        if (l >= r) return ll(0);
        
        // TODO: change
        
        auto [t, i] = s.query(l, r);
        // ll i = min_element(begin(a) + l, begin(a) + r + 1) - begin(a);
        
        ll j = i;
        for (; j <= r; ++j) {
            if (a[j] % a[i] == 0) continue;
            break;
        }
        
        ll k = i;
        
        for (; k >= l; --k) {
            if (a[k] % a[i] == 0) continue;
            break;
        }
        
        --j;
        ++k;

        if (i == l) {
            if (j == i) {
                return p + rec(i + 1, r);
            } else {
                return (j - i) * min(a[i], p) + rec(j, r);
            }
        } else if (i == r) {
            if (k == i) {
                return p + rec(l, i - 1);
            } else {
                return (i - k) * min(a[i], p) + rec(l, k);
            }
        }

        ll ans = 0;
        if (j == i) {
            ans += p + rec(i + 1, r);
        } else {
            ans += (j - i) * min(a[i], p) + rec(j, r);
        }
        if (k == i) {
            ans += p + rec(l, i - 1);
        } else {
            ans += (i - k) * min(a[i], p) + rec(l, k);
        }
        return ans;
    };
    cout << rec(0, n - 1) << '\n';
}

void brute(int) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute(_t);
    }
    return 0;
}
