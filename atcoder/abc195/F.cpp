// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")
// #pragma GCC optimize("unroll-loops")

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
//#include <ext/rope>

using namespace __gnu_pbds;
// using namespace __gnu_cxx;
using namespace std;

using ll = long long;

// #define int long long
#define unordered_map gp_hash_table
#define cauto const auto

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
 
template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) { return os << "(" << p.first << ", " << p.second << ")"; }
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
 
void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

// clang-format on

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;
constexpr long double pi = acosl(-1.0);
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
T pwr(T a, int64_t n) {
    T ans(1);
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

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

void solve(int) {
    ll a, b;
    cin >> a >> b;
    ll n = b - a + 1;

    vector<vector<int>> G(n, vector<int>(n));
    for (ll i = a; i <= b; ++i) {
        for (ll j = i + 1; j <= b; ++j) {
            if (__gcd(i, j) == 1) {
                G[i - a][j - a] = 1;
                G[j - a][i - a] = 1;
            }
        }
    }

    // this works if the problem asked for independent sets of pairs of cards
    // cout << y_combinator([&](auto solve, vector<vector<int>> g) -> uint64_t {
    //
    //     int n = g.size();
    //     vector<int> deg(n);
    //
    //     for (int i = 0; i < n; ++i) {
    //         for (int j = 0; j < n; ++j) {
    //             deg[i] += g[i][j];
    //         }
    //     }
    //
    //     int u = max_element(begin(deg), end(deg)) - begin(deg);
    //
    //     if (deg[u] == 0) {
    //         return 1ULL;
    //     } else if (deg[u] == 1) {
    //         int t = 0;
    //         for (int i = 0; i < n; ++i) {
    //             t += deg[i];
    //         }
    //         return 1ULL << (t / 2);
    //     }
    //
    //     int v = -1;
    //     int max_deg = -1;
    //
    //     for (int i = 0; i < n; ++i) {
    //         if (g[u][i] && deg[i] > max_deg) {
    //             v = i;
    //             max_deg = deg[i];
    //         }
    //     }
    //
    //     g[u][v] = 0;
    //     g[v][u] = 0;
    //
    //     if (n == 2) return 1ULL;
    //
    //     uint64_t x = solve(g);
    //
    //     if (u > v) swap(u, v);
    //
    //     g.erase(g.begin() + v);
    //     g.erase(g.begin() + u);
    //
    //     for (auto &gg : g) {
    //         gg.erase(gg.begin() + v);
    //         gg.erase(gg.begin() + u);
    //     }
    //
    //     return x + solve(g);
    // })(G) << '\n';
    // ;

    vector<int> is_prime(73, 1);
    vector<int> primes;
    for (int i = 0; i <= 72; ++i) {
        if (i <= 1)
            is_prime[i] = 0;
        else {
            for (int j = 2; j * j <= i; ++j) {
                if (i % j == 0) {
                    is_prime[i] = 0;
                }
            }
        }
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    n = primes.size();

    vector<uint64_t> dp((1 << n), 0);
    dp[0] = 1;

    for (ll i = a; i <= b; ++i) {
        ll m = 0;
        for (int j = 0; j < n; ++j) {
            if (i % primes[j] == 0) {
                m |= 1 << j;
            }
        }
        for (int j = 0; j < (1 << n); ++j) {
            if (!(j & m)) {
                dp[j | m] += dp[j];
            }
        }
    }

    uint64_t ans = 0;

    for (ll m = 0; m < (1 << n); ++m) {
        ans += dp[m];
    }

    cout << ans << '\n';
}

void brute(int) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute(_t);
    }
    return 0;
}
