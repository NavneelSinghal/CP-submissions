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

int mis(vector<vector<int>>& g) {
    int n = (int)g.size();
    int m = n >> 1;
    int p = n - m;

    int m_s = 1 << m;
    int p_s = 1 << p;

    int ans = 0;

    // individual mis
    vector<int> dp1(m_s), dp2(p_s);

    // singleton
    for (int i = 0; i < m; ++i) dp1[(1 << i)] = 1;
    for (int i = 0; i < m_s; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!((i >> j) & 1)) {
                int add = 1;
                for (int k = 0; k < m; ++k) {
                    if ((i >> k) & 1) {
                        add &= !g[j][k];
                    }
                }
                remax(dp1[i | (1 << j)], dp1[i] + add);
            }
        }
    }

    remax(ans, *max_element(begin(dp1), end(dp1)));

    for (int i = 0; i < p; ++i) dp2[(1 << i)] = 1;
    for (int i = 0; i < p_s; ++i) {
        for (int j = 0; j < p; ++j) {
            if (!((i >> j) & 1)) {
                int add = 1;
                for (int k = 0; k < p; ++k) {
                    if ((i >> k) & 1) {
                        add &= !g[j + m][k + m];
                    }
                }
                remax(dp2[i | (1 << j)], dp2[i] + add);
            }
        }
    }

    remax(ans, *max_element(begin(dp2), end(dp2)));

    // cross
    for (int i = 0; i < m_s; ++i) {
        if (dp1[i] > 0) {
            int subset = 0;
            for (int j = 0; j < m; ++j) {
                if ((i >> j) & 1) {
                    for (int k = 0; k < p; ++k) {
                        if (g[j][k + m]) {
                            subset |= (1 << k);
                        }
                    }
                }
            }
            remax(ans, dp1[i] + dp2[((1 << p) - 1) ^ subset]);
        }
    }

    return ans;

}

void solve(int) {
    int n, m;
    cin >> n >> m;
    map<string, int> id;
    int cur_id = 0;
    ll set1 = 0;
    vector<vector<int>> g(m, vector<int>(m));
    {
        int _;
        cin >> _;
    }
    for (int i = 1; i <= n; ++i) {
        int t;
        if (i != n) cin >> t;
        else t = 1;
        if (t == 1) {
            for (int i = 0; i < m; ++i) {
                for (int j = i + 1; j < m; ++j) {
                    if (((set1 >> i) & 1) && ((set1 >> j) & 1)) {
                        g[i][j] = 1;
                        g[j][i] = 1;
                    }
                }
            }
            set1 = 0;
        } else {
            string s;
            cin >> s;
            if (id.find(s) == id.end()) {
                id[s] = cur_id++;
            }
            set1 |= (1LL << id[s]);
        }
    }
    cout << mis(g) << '\n';
    return;
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
