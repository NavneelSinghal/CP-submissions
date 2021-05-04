// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")
// #pragma GCC optimize("unroll-loops")

// clang-format off
#define BITSET64 0
#if BITSET64
    #include <string>
    #include <bits/functexcept.h>
    #include <iosfwd>
    #include <bits/cxxabi_forced.h>
    #include <bits/functional_hash.h>
    #pragma push_macro("__SIZEOF_LONG__")
    #pragma push_macro("__cplusplus")
    #define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
    #define unsigned unsigned long
    #define __cplusplus 201102L
    #define __builtin_popcountl __builtin_popcountll
    #define __builtin_ctzl __builtin_ctzll
    #include <bitset>
    #pragma pop_macro("__cplusplus")
    #pragma pop_macro("__SIZEOF_LONG__")
    #undef unsigned
    #undef __builtin_popcountl
    #undef __builtin_ctzl
#endif
// clang-format on

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
// #include <ext/rope>

template <typename T>
void ignore_unused(const T &) {}

// #define int int_fast32_t

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using ulll = __uint128_t;
using lll = __int128;

namespace ExtendedIO {
#ifdef __SIZEOF_INT128__
    std::ostream &operator<<(std::ostream &os, __int128 const &value) {
        static char buffer[64];
        int index = 0;
        __uint128_t T = (value < 0) ? (-(value + 1)) + __uint128_t(1) : value;
        if (value < 0)
            os << '-';
        else if (T == 0)
            return os << '0';
        for (; T > 0; ++index) {
            buffer[index] = static_cast<char>('0' + (T % 10));
            T /= 10;
        }
        while (index > 0) os << buffer[--index];
        return os;
    }
    std::istream &operator>>(std::istream &is, __int128 &T) {
        static char buffer[64];
        is >> buffer;
        std::size_t len = strlen(buffer), index = 0;
        T = 0;
        int mul = 1;
        if (buffer[index] == '-') ++index, mul *= -1;
        for (; index < len; ++index)
            T = T * 10 + static_cast<int>(buffer[index] - '0');
        T *= mul;
        return is;
    }
#endif
}  // namespace ExtendedIO

using namespace ExtendedIO;

namespace Debug {

#define SFINAE(x, ...)             \
    template <class, class = void> \
    struct x : std::false_type {}; \
    template <class T>             \
    struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

    SFINAE(DefaultIO, decltype(std::cout << std::declval<T &>()));
    SFINAE(IsTuple, typename std::tuple_size<T>::type);
    SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

    template <class T>
    constexpr char Space(const T &) {
        return (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
    }

    template <auto &os>
    struct Writer {
        template <class T>
        void Impl(T const &t) const {
            if constexpr (DefaultIO<T>::value)
                os << t;
            else if constexpr (Iterable<T>::value) {
                int i = 0;
                for (auto &&x : t)
                    ((i++) ? (os << Space(x), Impl(x)) : Impl(x));
            } else if constexpr (IsTuple<T>::value)
                std::apply(
                    [this](auto const &... args) {
                        int i = 0;
                        (((i++) ? (os << ' ', Impl(args)) : Impl(args)), ...);
                    },
                    t);
            else
                static_assert(IsTuple<T>::value, "No matching type for print");
        }
        template <class F, class... Ts>
        auto &operator()(F const &f, Ts const &... ts) const {
            return Impl(f), ((os << ' ', Impl(ts)), ...), os << '\n', *this;
        }
    };

    template <auto &is>
    struct Reader {
        template <class T>
        auto &Rd(T &t) const {
            if constexpr (DefaultIO<T>::value)
                is >> t;
            else if constexpr (Iterable<T>::value)
                for (auto &x : t) Rd(x);
            else if constexpr (IsTuple<T>::value)
                std::apply([this](auto &... args) { (Rd(args), ...); }, t);
            else
                static_assert(IsTuple<T>::value, "No matching type for read");
            return *this;
        }
        template <class T>
        auto operator()(T t) const {
            Rd(t);
            return t;
        }
    };

#ifdef DEBUG
    #define debug(args...)                               \
        {                                                \
            std::string _s = #args;                      \
            replace(_s.begin(), _s.end(), ',', ' ');     \
            std::stringstream _ss(_s);                   \
            std::istream_iterator<std::string> _it(_ss); \
            std::cerr << "Line " << __LINE__ << "\n";    \
            err(_it, args);                              \
        }

    void err(std::istream_iterator<std::string> it) { ignore_unused(it); }

    template <typename T, typename... Args>
    void err(std::istream_iterator<std::string> it, T a, Args... args) {
        std::cerr << "\033[0;31m" << *it << " = ";
        Writer<std::cerr>{}(a);
        std::cerr << "\033[0m";
        err(++it, args...);
    }

    #define ASSERT(...) \
        if (not(__VA_ARGS__)) throw runtime_error(#__VA_ARGS__)
#else
    #define debug(...) 0
    #define ASSERT(...) 0
#endif

    constexpr Writer<std::cout> print;
    constexpr Reader<std::cin> read;

}  // namespace Debug

using namespace Debug;

namespace CPPDS {

#ifdef PB_DS_ASSOC_CNTNR_HPP
    #define unordered_map gp_hash_table
#endif

#ifdef PB_DS_TREE_POLICY_HPP
    template <typename T>
    using ordered_set =
        __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,
                         __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>;
    template <typename T>
    using ordered_multiset =
        __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less_equal<T>,
                         __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>;
    template <class key, class value, class cmp = std::less<key>>
    using ordered_map =
        __gnu_pbds::tree<key, value, cmp, __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>;
    // find_by_order(k)  returns iterator to kth element starting from 0;
    // order_of_key(k) returns count of elements strictly smaller than k;
    // for ordered_multiset, lower_bound and upper_bound swap roles
#endif
    template <class T>
    using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
}  // namespace CPPDS

using namespace CPPDS;

namespace Utility {

    void setIO(std::string name = "") {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
        std::cin.exceptions(std::cin.failbit);
        std::cout << std::setprecision(20) << std::fixed;
        if (name.size() == 0) return;
        ignore_unused(freopen((name + ".in").c_str(), "r", stdin));
        ignore_unused(freopen((name + ".out").c_str(), "w", stdout));
    }

    constexpr int mod = int(1e9) + 7;
    constexpr int nttmod = 998244353;
    constexpr int inf = int(1e9);
    constexpr ll linf = ll(3e18L);
    constexpr ld eps = 1e-9;
    ld pi = acosl(-1.0);

    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());

    template <typename C = std::chrono::steady_clock,
              typename T1 = std::chrono::nanoseconds,
              typename T2 = std::chrono::milliseconds>
    struct Stopwatch {
        std::string name;
        std::chrono::time_point<C> last_played;
        T1 elapsed_time;
        bool running;
        Stopwatch(const std::string &s) : name(s), running(true) { reset(); }
        Stopwatch() : Stopwatch("Time") {}
        void reset() {
            last_played = C::now();
            elapsed_time = T1::zero();
        }
        void pause() {
            if (!running) return;
            running = false;
            elapsed_time +=
                std::chrono::duration_cast<T1>(C::now() - last_played);
        }
        void play() {
            if (running) return;
            running = true;
            last_played = C::now();
        }
        int_fast64_t elapsed() const {
            return std::chrono::duration_cast<T2>(
                       elapsed_time + (running ? std::chrono::duration_cast<T1>(
                                                     C::now() - last_played)
                                               : T1::zero()))
                .count();
        }
        void print() const {
#ifdef TIMING
            std::cerr << name << ": " << elapsed() << " ms\n";
#endif
        }
        ~Stopwatch() { print(); }
    };

    template <class T, class U = T>
    bool ckmin(T &a, U &&b) {
        return b < a ? a = std::forward<U>(b), true : false;
    }

    template <class T, class U = T>
    bool ckmax(T &a, U &&b) {
        return a < b ? a = std::forward<U>(b), true : false;
    }

    template <typename T>
    inline T sq(T a) {
        return a * a;
    }

    template <typename T>
    inline T sq_dist(std::pair<T, T> &a, std::pair<T, T> &b) {
        return sq(a.first - b.first) + sq(a.second - b.second);
    }

    template <typename T>
    inline ld dist(std::pair<T, T> &a, std::pair<T, T> &b) {
        return sqrtl(sq_dist(a, b));
    }

    inline ll isqrt(ll n) {
        ll sq = (ll)sqrtl((ld)n) - 2;
        sq = std::max(sq, ll(0));
        while (sq * sq < n) sq++;
        if ((sq * sq) == n) return sq;
        return sq - 1;
    }

    inline bool is_sq(ll n) {
        ll w = isqrt(n);
        return w * w == n;
    }

    struct custom_hash {
        // http://xorshift.di.unimi.it/splitmix64.c
        static ull splitmix64(ull x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(ull x) const {
            static const ull FIXED_RANDOM =
                std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }

        size_t operator()(std::pair<int, int> p) const {
            static const ull FIXED_RANDOM =
                std::chrono::steady_clock::now().time_since_epoch().count();
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

    template <typename T>
    struct Range {
        struct It {
            T i;
            const T skip;
            void operator++() { i += skip; }
            T operator*() const { return i; }
            bool operator!=(It o) const {
                return (skip >= 0) ? (i < *o) : (i > *o);
            }
        };
        const T l_, r_, skip_;
        Range(T l, T r, T skip = 1) : l_(l), r_(r), skip_(skip) {
#ifdef DEBUG
            assert(skip != 0);
#endif
        }
        Range(T n) : Range(T(0), n, T(1)) {}
        It begin() const {
            return (skip_ >= 0) ? It{l_, skip_} : It{r_ - 1, skip_};
        }
        It end() const {
            return (skip_ >= 0) ? It{r_, skip_} : It{l_ - 1, skip_};
        }
    };

    // when using integers, keep overflow in mind
    template <typename T>
    [[nodiscard]] T pwr(T a, ll n) {
        T ans(1);
        while (n) {
            if (n & 1) ans *= a;
            if (n > 1) a *= a;
            n >>= 1;
        }
        return ans;
    }

    template <typename I, typename P, bool b>
    I bin_search_split(I l, I r, const P &predicate) {
        --l, ++r;
        while (r - l > 1) {
            // auto mid = std::midpoint(l, r);
            auto mid = l + (r - l) / 2;
            if (predicate(mid))
                r = mid;
            else
                l = mid;
        }
        if constexpr (b)
            return r;
        else
            return l;
    }

    // returns first i in [l, r], p(i) true, and if none found, returns r + 1
    template <typename I, typename P>
    I first_true(I l, I r, const P &p) {
        return bin_search_split<I, P, true>(l, r, p);
    }

    // returns last i in [l, r], p(i) false, and if none found, returns l - 1
    template <typename I, typename P>
    I last_false(I l, I r, const P &p) {
        return bin_search_split<I, P, false>(l, r, p);
    }

}  // namespace Utility

using namespace Utility;

/* structs start */

template <uint32_t Modulus>
class Modular {
    using M = Modular;

   public:
    static_assert(int(Modulus) >= 1, "Modulus must be in the range [1, 2^31)");
    static constexpr int modulus() { return Modulus; }
    static M raw(uint32_t v) { return *reinterpret_cast<M *>(&v); }
    Modular() : v_(0) {}
    Modular(int64_t v) : v_((v %= Modulus) < 0 ? v + Modulus : v) {}
    template <class T>
    explicit operator T() const {
        return v_;
    }
    M &operator++() { return v_ = ++v_ == Modulus ? 0 : v_, *this; }
    M &operator--() { return --(v_ ? v_ : v_ = Modulus), *this; }
    M &operator*=(M o) { return v_ = uint64_t(v_) * o.v_ % Modulus, *this; }
    M &operator/=(M o) {
        auto [inv, gcd] = extgcd(o.v_, Modulus);
        assert(gcd == 1);
        return *this *= inv;
    }
    M &operator+=(M o) {
        return v_ = int(v_ += o.v_ - Modulus) < 0 ? v_ + Modulus : v_, *this;
    }
    M &operator-=(M o) {
        return v_ = int(v_ -= o.v_) < 0 ? v_ + Modulus : v_, *this;
    }
    friend M operator++(M &a, int) { return exchange(a, ++M(a)); }
    friend M operator--(M &a, int) { return exchange(a, --M(a)); }
    friend M operator+(M a) { return a; }
    friend M operator-(M a) { return a.v_ = a.v_ ? Modulus - a.v_ : 0, a; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a /= b; }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    friend std::istream &operator>>(std::istream &is, M &x) {
        int64_t v;
        return is >> v, x = v, is;
    }
    friend std::ostream &operator<<(std::ostream &os, M x) {
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

/* structs end */

using namespace std;
using namespace __gnu_pbds;
// using namespace __gnu_cxx;

/* main code starts */

struct LazySegTree {
    struct node_t {
        int mn;
        long long sum;
        int sz;
    };

    using base_t = int;
    using update_t = int;

    // struct update_t {
    //     long long remx;
    // };

    // combining two nodes
    node_t combine(const node_t &n1, const node_t &n2) {
        return node_t{std::min(n1.mn, n2.mn), n1.sum + n2.sum, n1.sz + n2.sz};
    }

    // create node from base value and indices l, r
    node_t make_node(const base_t &val, int l, int r) { return {val, val, 1}; }

    // node corresponding to empty interval
    node_t id_node() { return {inf + 1, 0, 0}; }

    // apply update u to the whole node n
    node_t apply_update(const update_t &u, const node_t &nd) {
        // assume that updates are applied as assignments
        if (u == 0) return nd;  // id
        return {u, 1LL * u * nd.sz, nd.sz};
    }

    // effective update if v is applied to node, followed by u
    update_t compose_updates(const update_t &u, const update_t &v) {
        return {std::max(u, v)};
    }

    // identity update
    update_t id_update() { return 0; }

    std::vector<node_t> t;
    std::vector<update_t> lazy;
    int n;

    LazySegTree(std::vector<base_t> &a) {
        this->n = a.size();
        if (this->n == 0) return;
        this->t.assign(4 * a.size(), id_node());
        this->lazy.assign(2 * a.size(), id_update());
        _build(1, 0, n, a);
    }

    // half open
    void update(int l, int r, const update_t &u) { _update(1, 0, n, l, r, u); }
    node_t query(int l, int r) { return _query(1, 0, n, l, r); }

    // find least R in [l, n] such that f(combine(a[l..r])) is false
    // and f(combine(a[l..r-1])) = true
    // Requires f to be contiguous (possibly empty) segments of true and false
    template <bool b, typename F>
    int first_false_right(int l, const F &f) {
        auto acc = id_node();
        // assert(f(acc));
        auto i = _first_false_right<b, F>(1, 0, n, l, n, f, acc);
        if (i == -1) return n;
        return i;
    }

    // helper functions
    void _pullUp(int v) { t[v] = combine(t[2 * v], t[2 * v + 1]); }
    void _updateNode(int v, const update_t &u) {
        t[v] = apply_update(u, t[v]);
        if (v < (int)lazy.size()) lazy[v] = compose_updates(u, lazy[v]);
    }
    void _pushDown(int v) {
        _updateNode(2 * v, lazy[v]);
        _updateNode(2 * v + 1, lazy[v]);
        lazy[v] = id_update();
    }

    // actual functions
    void _build(int v, int l, int r, const std::vector<base_t> &a) {
        if (l == r - 1) {
            t[v] = make_node(a[l], l, r);
            return;
        }
        int mid = (l + r) / 2;
        _build(2 * v, l, mid, a);
        _build(2 * v + 1, mid, r, a);
        _pullUp(v);
    }

    void _update(int v, int l, int r, int ql, int qr, const update_t &u) {
        if (qr <= l || r <= ql) return;  // empty intersection
        if (ql <= l && r <= qr) {        // completely inside query
            _updateNode(v, u);
            return;
        }
        _pushDown(v);
        int mid = (l + r) / 2;
        _update(2 * v, l, mid, ql, qr, u);
        _update(2 * v + 1, mid, r, ql, qr, u);
        _pullUp(v);
    }

    node_t _query(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return id_node();  // empty intersection
        if (ql <= l && r <= qr) return t[v];       // completely inside query
        _pushDown(v);
        int mid = (l + r) / 2;
        return combine(_query(2 * v, l, mid, ql, qr),
                       _query(2 * v + 1, mid, r, ql, qr));
    }

    // find least R in [l, r] such that f(combine(a[ql..R])) is false
    // and f(combine(a[ql..R-1])) = true. -1 if not found
    // Requires f to be contiguous (possibly empty) segments of true and false
    template <bool b, typename F>
    int _first_false_right(int v, int l, int r, int ql, int qr, const F &f,
                           node_t &acc) {
        if (r <= ql) return -1;
        if (qr <= l) return l;
        auto new_acc = combine(acc, t[v]);
        if (ql <= l && r <= qr) {
            if (f(new_acc)) {
                acc = new_acc;
                return -1;
            }
            while (r - l > 1) {
                int mid = (r + l) / 2;
                if constexpr (b) _pushDown(v);
                new_acc = combine(acc, t[2 * v]);
                if (!f(new_acc)) {
                    v *= 2;
                    r = mid;
                } else {
                    acc = std::move(new_acc);
                    v = 2 * v + 1;
                    l = mid;
                }
            }
            return l;
        }
        if (l == r - 1) return l;
        if constexpr (b) _pushDown(v);
        int mid = (r + l) / 2;
        auto res = _first_false_right<b, F>(2 * v, l, mid, ql, qr, f, acc);
        if (res != -1)
            return res;
        else
            return _first_false_right<b, F>(2 * v + 1, mid, r, ql, qr, f, acc);
    }
};

namespace IO {
#define CUSTOM_IO
    using namespace std;
    const int BUFFER_SIZE = 1 << 15;

    char input_buffer[BUFFER_SIZE];
    size_t input_pos = 0, input_len = 0;

    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;

    char number_buffer[100];
    uint8_t lookup[100];

    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;

        if (input_len == 0) input_buffer[0] = EOF;
    }

    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();

        return input_buffer[advance ? input_pos++ : input_pos];
    }

    inline bool isspace(char c) {
        return (unsigned char)(c - '\t') < 5 || c == ' ';
    }

    inline void read_char(char &c) {
        while (isspace(next_char(false))) next_char();

        c = next_char();
    }

    template <typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;

        while (!isdigit(next_char(false)))
            if (next_char() == '-') negative = true;

        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));

        if (negative) number = -number;
    }

    template <typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }

    inline void read_str(string &str) {
        while (isspace(next_char(false))) next_char();

        str.clear();

        do {
            str += next_char();
        } while (!isspace(next_char(false)));
    }

    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }

    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();

        output_buffer[output_pos++] = c;
    }

    template <typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }

        int length = 0;

        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = char((lookup_value & 15) + '0');
            number_buffer[length++] = char((lookup_value >> 4) + '0');
        }

        if (number != 0 || length == 0) write_char(char(number + '0'));

        for (int i = length - 1; i >= 0; i--) write_char(number_buffer[i]);

        if (after) write_char(after);
    }

    inline void write_str(const string &str, char after = '\0') {
        for (char c : str) write_char(c);

        if (after) write_char(after);
    }

    void IOinit() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);

        for (int i = 0; i < 100; i++)
            lookup[i] = uint8_t((i / 10 << 4) + i % 10);
    }
}  // namespace IO

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
        int n, q;
        IO::read_int(n, q);
        vector<int> a(n);
        for (auto &x : a) IO::read_int(x);
        LazySegTree st(a);
        while (q--) {
            int t, x, y;
            IO::read_int(t, x, y);
            --x;
            if (t == 1) {
                int start = st.first_false_right<false>(
                    0, [&](const LazySegTree::node_t &node) {
                        return node.mn >= y;
                    });
                if (start <= x) st.update(start, x + 1, y);
            } else {
                int ans = 0;
                while (y > 0 && x < n) {
                    x = st.first_false_right<false>(
                        x, [&](const LazySegTree::node_t &node) {
                            return node.mn > y;
                        });
                    if (x == n) break;
                    int endpoint = st.first_false_right<true>(
                        x, [&](const LazySegTree::node_t &node) {
                            return node.sum <= y;
                        });
                    ans += endpoint - x;
                    y -= st.query(x, endpoint).sum;
                    x = endpoint;
                }
                IO::write_int(ans, '\n');
            }
        }
    };

    auto brute = [&]() -> void {
    };

    ignore_unused(brute);
    precompute();
    for (int _t = 1; _t <= TESTS; ++_t) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute();
    }
    return 0;
}