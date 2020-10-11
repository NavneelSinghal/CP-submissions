#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#pragma GCC optimize ("unroll-loops")

// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//#include <ext/rope>

using namespace __gnu_pbds;

//using namespace __gnu_cxx;

using namespace std;

//#define int long long
//#define double long double
#define Int signed
#define vi vector<int>
#define vI vector<Int>
#define vvi vector<vi>
#define vvI vector<vI>
#define vd vector<double>
#define vvd vector<vd>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mii map<int, int>
#define unordered_map gp_hash_table

#define OVERLOADED_MACRO(M, ...) _OVR(M, _COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)
#define _OVR(macroName, number_of_args)   _OVR_EXPAND(macroName, number_of_args)
#define _OVR_EXPAND(macroName, number_of_args)    macroName##number_of_args

#define _COUNT_ARGS(...)  _ARG_PATTERN_MATCH(__VA_ARGS__, 9,8,7,6,5,4,3,2,1)
#define _ARG_PATTERN_MATCH(_1,_2,_3,_4,_5,_6,_7,_8,_9, N, ...)   N

#define rep(...) OVERLOADED_MACRO(rep, __VA_ARGS__)
#define repd(...) OVERLOADED_MACRO(repd, __VA_ARGS__)

#define rep3(i, a, b) for (int i = a; i < b; ++i)
#define rep2(i, n) rep3(i, 0, n)
#define repd3(i, a, b) for(int i = b - 1; i >= a; --i)
#define repd2(i, n) repd3(i, 0, n)
#define rep4(i, a, b, c) for(int i = a; i < b; i += c)

#define F first
#define S second

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

#define bitcount __builtin_popcountll
//for trailing 1s, do trailing0(n + 1)
#define leading0 __builtin_clzll
#define trailing0 __builtin_ctzll
#define isodd(n) (n & 1)
#define iseven(n) (!(n & 1))

#define sz(v) ((int) v.size())
#define del_rep(v) sort(all(v)); v.erase(unique(all(v)), v.end());
#define checkbit(n, b) ((n >> b) & 1)

#ifdef DEBUG
#define debug(args...) {\
    std::string _s = #args;\
    replace(_s.begin(), _s.end(), ',', ' ');\
    std::stringstream _ss(_s);\
    std::istream_iterator <std::string> _it(_ss);\
    err(_it, args);\
}
#define print_container(v) {\
    bool first = true; os << "[";\
    for (auto x : v) {\
        if (!first) os << ", "; os << x; first = false;\
    }\
    return os << "]";\
}
void err (std::istream_iterator <std::string> it) {}
template <typename T, typename... Args>
void err (std::istream_iterator <std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}
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

namespace IO {
    const int BUFFER_SIZE = 1 << 15;
    char input_buffer[BUFFER_SIZE];
    size_t input_pos = 0, input_len = 0;
    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
    char number_buffer[100];
    uint8_t lookup[100];
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin); input_pos = 0;
        if (input_len == 0) input_buffer[0] = EOF;
    }
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();
        return input_buffer[advance ? input_pos++ : input_pos];
    }
    inline bool isspace(char c) {
        return (unsigned char) (c - '\t') < 5 || c == ' ';
    }
    inline void read_char(char &c) {
        while (isspace(next_char(false))) next_char();
        c = next_char();
    }
    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
        while (!isdigit(next_char(false))) if (next_char() == '-') negative = true;
        do {number = 10 * number + (next_char() - '0');} while (isdigit(next_char(false)));
        if (negative) number = -number;
    }
    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
    inline void read_str(string &str) {
        while (isspace(next_char(false))) next_char();
        str.clear();
        do {str += next_char();} while (!isspace(next_char(false)));
    }
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();
        output_buffer[output_pos++] = c;
    }
    template<typename T>
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
        for (int i = 0; i < 100; i++) lookup[i] = uint8_t((i / 10 << 4) + i % 10);
    }
}

using namespace IO;

struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<int, int> x) const { 
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(FIXED_RANDOM + 31 * x.first + x.second);
    }
};

//order_of_key(k) - number of elements e such that func(e, k) returns true, where func is less or less_equal
//find_by_order(k) - kth element in the set counting from 0

typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

const int INF = 1e9;
const int LINF = INF * INF;
const double EPS = 1e-9;
const double PI = acosl(-1);

template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}

template <unsigned Mod = 998244353> 
struct Modular {
    using M = Modular;
    unsigned v;
    Modular(long long a = 0) : v((a %= Mod) < 0 ? a + Mod : a) {}
    M operator-() const { return M() -= *this; }
    M& operator+=(M r) { if ((v += r.v) >= Mod) v -= Mod; return *this; }
    M& operator-=(M r) { if ((v += Mod - r.v) >= Mod) v -= Mod; return *this; }
    M& operator*=(M r) { v = (uint64_t)v * r.v % Mod; return *this; }
    M& operator/=(M r) { return *this *= pwr(r, Mod - 2); }
    friend M operator+(M l, M r) { return l += r; }
    friend M operator-(M l, M r) { return l -= r; }
    friend M operator*(M l, M r) { return l *= r; }
    friend M operator/(M l, M r) { return l /= r; }
    friend bool operator==(M l, M r) { return l.v == r.v; }
    friend bool operator!=(M l, M r) { return l.v != r.v; }
    friend ostream& operator<<(ostream& os, M a) { return os << a.v; }
    friend istream& operator>>(istream& is, M &a) { int64_t w; is >> w; a = M(w); return is; }
};

const int Mod = 1e9 + 7;

using mint = Modular<Mod>;

const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size() == 0) return;
    FILE* fin = freopen((name+".in").c_str(), "r", stdin);
    FILE* fout = freopen((name+".out").c_str(), "w", stdout);
}

namespace algebra {
    const int32_t inf = 1e9;
    const int32_t magic = 500;  // threshold for sizes to run the naive algo

    namespace fft {
        const int32_t maxn = 1 << 18;

        typedef double ftype;
        typedef complex<ftype> point;

        point w[maxn];
        const ftype pi = acos(-1);
        bool initiated = 0;
        void init() {
            if (!initiated) {
                for (int32_t i = 1; i < maxn; i *= 2) {
                    for (int32_t j = 0; j < i; j++) {
                        w[i + j] = polar(ftype(1), pi * j / i);
                    }
                }
                initiated = 1;
            }
        }
        template <typename T>
            void fft(T* in, point* out, int32_t n, int32_t k = 1) {
                if (n == 1) {
                    *out = *in;
                } else {
                    n /= 2;
                    fft(in, out, n, 2 * k);
                    fft(in + k, out + n, n, 2 * k);
                    for (int32_t i = 0; i < n; i++) {
                        auto t = out[i + n] * w[i + n];
                        out[i + n] = out[i] - t;
                        out[i] += t;
                    }
                }
            }

        template <typename T>
            void mul_slow(vector<T>& a, const vector<T>& b) {
                vector<T> res(a.size() + b.size() - 1);
                for (size_t i = 0; i < a.size(); i++) {
                    for (size_t j = 0; j < b.size(); j++) {
                        res[i + j] += a[i] * b[j];
                    }
                }
                a = res;
            }

        template <typename T>
            void mul(vector<T>& a, const vector<T>& b) {
                if (min(a.size(), b.size()) < magic) {
                    mul_slow(a, b);
                    return;
                }
                init();
                static const int32_t shift = 15, mask = (1 << shift) - 1;
                size_t n = a.size() + b.size() - 1;
                while (__builtin_popcount(n) != 1) {
                    n++;
                }
                a.resize(n);
                static point A[maxn], B[maxn];
                static point C[maxn], D[maxn];
                for (size_t i = 0; i < n; i++) {
                    A[i] = point(a[i] & mask, a[i] >> shift);
                    if (i < b.size()) {
                        B[i] = point(b[i] & mask, b[i] >> shift);
                    } else {
                        B[i] = 0;
                    }
                }
                fft(A, C, n);
                fft(B, D, n);
                for (size_t i = 0; i < n; i++) {
                    point c0 = C[i] + conj(C[(n - i) % n]);
                    point c1 = C[i] - conj(C[(n - i) % n]);
                    point d0 = D[i] + conj(D[(n - i) % n]);
                    point d1 = D[i] - conj(D[(n - i) % n]);
                    A[i] = c0 * d0 - point(0, 1) * c1 * d1;
                    B[i] = c0 * d1 + d0 * c1;
                }
                fft(A, C, n);
                fft(B, D, n);
                reverse(C + 1, C + n);
                reverse(D + 1, D + n);
                int32_t t = 4 * n;
                for (size_t i = 0; i < n; i++) {
                    int64_t A0 = llround(real(C[i]) / t);
                    T A1 = llround(imag(D[i]) / t);
                    T A2 = llround(imag(C[i]) / t);
                    a[i] = A0 + (A1 << shift) + (A2 << 2 * shift);
                }
                return;
            }
    }  // namespace fft
    template <typename T>
        T bpow(T x, size_t n) {
            return n ? n % 2 ? x * bpow(x, n - 1) : bpow(x * x, n / 2) : T(1);
        }
    template <typename T>
        T bpow(T x, size_t n, T m) {
            return n ? n % 2 ? x * bpow(x, n - 1, m) % m : bpow(x * x % m, n / 2, m)
                : T(1);
        }
    template <typename T>
        T gcd(const T& a, const T& b) {
            return b == T(0) ? a : gcd(b, a % b);
        }
    template <typename T>
        T nCr(T n, int32_t r) {  // runs in O(r)
            T res(1);
            for (int32_t i = 0; i < r; i++) {
                res *= (n - T(i));
                res /= (i + 1);
            }
            return res;
        }

    template <int32_t m>
        struct modular {
            int64_t r;
            modular() : r(0) {}
            modular(int64_t rr) : r(rr) {
                if (abs(r) >= m) r %= m;
                if (r < 0) r += m;
            }
            modular inv() const { return bpow(*this, m - 2); }
            modular operator*(const modular& t) const { return (r * t.r) % m; }
            modular operator/(const modular& t) const { return *this * t.inv(); }
            modular operator+=(const modular& t) {
                r += t.r;
                if (r >= m) r -= m;
                return *this;
            }
            modular operator-=(const modular& t) {
                r -= t.r;
                if (r < 0) r += m;
                return *this;
            }
            modular operator+(const modular& t) const { return modular(*this) += t; }
            modular operator-(const modular& t) const { return modular(*this) -= t; }
            modular operator*=(const modular& t) { return *this = *this * t; }
            modular operator/=(const modular& t) { return *this = *this / t; }

            bool operator==(const modular& t) const { return r == t.r; }
            bool operator!=(const modular& t) const { return r != t.r; }

            operator int64_t() const { return r; }
        };
    template <int32_t T>
        istream& operator>>(istream& in, modular<T>& x) {
            return in >> x.r;
        }

    template <typename T>
        struct poly {
            vector<T> a;

            void normalize() {  // get rid of leading zeroes
                while (!a.empty() && a.back() == T(0)) {
                    a.pop_back();
                }
            }

            poly() {}
            poly(T a0) : a{a0} { normalize(); }
            poly(vector<T> t) : a(t) { normalize(); }

            poly operator+=(const poly& t) {
                a.resize(max(a.size(), t.a.size()));
                for (size_t i = 0; i < t.a.size(); i++) {
                    a[i] += t.a[i];
                }
                normalize();
                return *this;
            }
            poly operator-=(const poly& t) {
                a.resize(max(a.size(), t.a.size()));
                for (size_t i = 0; i < t.a.size(); i++) {
                    a[i] -= t.a[i];
                }
                normalize();
                return *this;
            }
            poly operator+(const poly& t) const { return poly(*this) += t; }
            poly operator-(const poly& t) const { return poly(*this) -= t; }

            poly mod_xk(size_t k) const {  // get same polynomial mod x^k
                k = min(k, a.size());
                return vector<T>(begin(a), begin(a) + k);
            }
            poly mul_xk(size_t k) const {  // multiply by x^k
                poly res(*this);
                res.a.insert(begin(res.a), k, 0);
                return res;
            }
            poly div_xk(size_t k) const {  // divide by x^k, dropping coefficients
                k = min(k, a.size());
                return vector<T>(begin(a) + k, end(a));
            }
            poly substr(size_t l, size_t r) const {  // return mod_xk(r).div_xk(l)
                l = min(l, a.size());
                r = min(r, a.size());
                return vector<T>(begin(a) + l, begin(a) + r);
            }
            poly inv(size_t n) const {  // get inverse series mod x^n
                assert(!is_zero());
                poly ans = a[0].inv();
                size_t a = 1;
                while (a < n) {
                    poly C = (ans * mod_xk(2 * a)).substr(a, 2 * a);
                    ans -= (ans * C).mod_xk(a).mul_xk(a);
                    a *= 2;
                }
                return ans.mod_xk(n);
            }

            // change fft to ntt if using modulo
            poly operator*=(const poly& t) {
                fft::mul(a, t.a);
                // ntt::mul(a, t.a);
                normalize();
                return *this;
            }
            poly operator*(const poly& t) const { return poly(*this) *= t; }

            poly reverse(size_t n,
                    bool rev = 0) const {  // reverses and leaves only n terms
                poly res(*this);
                if (rev) {  // If rev = 1 then tail goes to head
                    res.a.resize(max(n, res.a.size()));
                }
                std::reverse(res.a.begin(), res.a.end());
                return res.mod_xk(n);
            }

            pair<poly, poly> divmod_slow(
                    const poly& b) const {  // when divisor or quotient is small
                vector<T> A(a);
                vector<T> res;
                while (A.size() >= b.a.size()) {
                    res.push_back(A.back() / b.a.back());
                    if (res.back() != T(0)) {
                        for (size_t i = 0; i < b.a.size(); i++) {
                            A[A.size() - i - 1] -= res.back() * b.a[b.a.size() - i - 1];
                        }
                    }
                    A.pop_back();
                }
                std::reverse(begin(res), end(res));
                return {res, A};
            }

            pair<poly, poly> divmod(
                    const poly& b) const {  // returns quotiend and remainder of a mod b
                if (deg() < b.deg()) {
                    return {poly{0}, *this};
                }
                int32_t d = deg() - b.deg();
                if (min(d, b.deg()) < magic) {
                    return divmod_slow(b);
                }
                poly D = (reverse(d + 1) * b.reverse(d + 1).inv(d + 1))
                    .mod_xk(d + 1)
                    .reverse(d + 1, 1);
                return {D, *this - D * b};
            }

            poly operator/(const poly& t) const { return divmod(t).first; }
            poly operator%(const poly& t) const { return divmod(t).second; }
            poly operator/=(const poly& t) { return *this = divmod(t).first; }
            poly operator%=(const poly& t) { return *this = divmod(t).second; }
            poly operator*=(const T& x) {
                for (auto& it : a) {
                    it *= x;
                }
                normalize();
                return *this;
            }
            poly operator/=(const T& x) {
                for (auto& it : a) {
                    it /= x;
                }
                normalize();
                return *this;
            }
            poly operator*(const T& x) const { return poly(*this) *= x; }
            poly operator/(const T& x) const { return poly(*this) /= x; }

            void print() const {
                for (auto it : a) {
                    cout << it << ' ';
                }
                cout << endl;
            }
            T eval(T x) const {  // evaluates in single point x
                T res(0);
                for (int32_t i = int32_t(a.size()) - 1; i >= 0; i--) {
                    res *= x;
                    res += a[i];
                }
                return res;
            }

            T& lead() {  // leading coefficient
                return a.back();
            }
            int32_t deg() const {  // degree
                return a.empty() ? -inf : a.size() - 1;
            }
            bool is_zero() const {  // is polynomial zero
                return a.empty();
            }
            T operator[](int32_t idx) const {
                return idx >= (int)a.size() || idx < 0 ? T(0) : a[idx];
            }

            T& coef(size_t idx) {  // mutable reference at coefficient
                return a[idx];
            }
            bool operator==(const poly& t) const { return a == t.a; }
            bool operator!=(const poly& t) const { return a != t.a; }

            poly deriv() {  // calculate derivative
                vector<T> res;
                for (int32_t i = 1; i <= deg(); i++) {
                    res.push_back(T(i) * a[i]);
                }
                return res;
            }
            poly integr() {  // calculate integral with C = 0
                vector<T> res = {0};
                for (int32_t i = 0; i <= deg(); i++) {
                    res.push_back(a[i] / T(i + 1));
                }
                return res;
            }
            size_t leading_xk() const {  // Let p(x) = x^k * t(x), return k
                if (is_zero()) {
                    return inf;
                }
                int32_t res = 0;
                while (a[res] == T(0)) {
                    res++;
                }
                return res;
            }
            poly log(size_t n) {  // calculate log p(x) mod x^n
                assert(a[0] == T(1));
                return (deriv().mod_xk(n) * inv(n)).integr().mod_xk(n);
            }
            poly exp(size_t n) {  // calculate exp p(x) mod x^n
                if (is_zero()) {
                    return T(1);
                }
                assert(a[0] == T(0));
                poly ans = T(1);
                size_t a = 1;
                while (a < n) {
                    poly C = ans.log(2 * a).div_xk(a) - substr(a, 2 * a);
                    ans -= (ans * C).mod_xk(a).mul_xk(a);
                    a *= 2;
                }
                return ans.mod_xk(n);
            }
            poly pow_slow(size_t k, size_t n) {  // if k is small
                return k ? k % 2 ? (*this * pow_slow(k - 1, n)).mod_xk(n)
                    : (*this * *this).mod_xk(n).pow_slow(k / 2, n)
                    : T(1);
            }
            poly pow(size_t k, size_t n) {  // calculate p^k(n) mod x^n
                if (is_zero()) {
                    return *this;
                }
                if (k < magic) {
                    return pow_slow(k, n);
                }
                int32_t i = leading_xk();
                T j = a[i];
                poly t = div_xk(i) / j;
                return bpow(j, k) * (t.log(n) * T(k)).exp(n).mul_xk(i * k).mod_xk(n);
            }
            poly mulx(T x) {  // component-wise multiplication with x^k
                T cur = 1;
                poly res(*this);
                for (int32_t i = 0; i <= deg(); i++) {
                    res.coef(i) *= cur;
                    cur *= x;
                }
                return res;
            }
            poly mulx_sq(T x) {  // component-wise multiplication with x^{k^2}
                T cur = x;
                T total = 1;
                T xx = x * x;
                poly res(*this);
                for (int32_t i = 0; i <= deg(); i++) {
                    res.coef(i) *= total;
                    total *= cur;
                    cur *= xx;
                }
                return res;
            }
            vector<T> chirpz_even(
                    T z, int32_t n) {  // P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
                int32_t m = deg();
                if (is_zero()) {
                    return vector<T>(n, 0);
                }
                vector<T> vv(m + n);
                T zi = z.inv();
                T zz = zi * zi;
                T cur = zi;
                T total = 1;
                for (int32_t i = 0; i <= max(n - 1, m); i++) {
                    if (i <= m) {
                        vv[m - i] = total;
                    }
                    if (i < n) {
                        vv[m + i] = total;
                    }
                    total *= cur;
                    cur *= zz;
                }
                poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
                vector<T> res(n);
                for (int32_t i = 0; i < n; i++) {
                    res[i] = w[i];
                }
                return res;
            }
            vector<T> chirpz(T z, int32_t n) {  // P(1), P(z), P(z^2), ..., P(z^(n-1))
                auto even = chirpz_even(z, (n + 1) / 2);
                auto odd = mulx(z).chirpz_even(z, n / 2);
                vector<T> ans(n);
                for (int32_t i = 0; i < n / 2; i++) {
                    ans[2 * i] = even[i];
                    ans[2 * i + 1] = odd[i];
                }
                if (n % 2 == 1) {
                    ans[n - 1] = even.back();
                }
                return ans;
            }
            template <typename iter>
                vector<T> eval(vector<poly>& tree, int32_t v, iter l,
                        iter r) {  // auxiliary evaluation function
                    if (r - l == 1) {
                        return {eval(*l)};
                    } else {
                        auto m = l + (r - l) / 2;
                        auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m);
                        auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, m, r);
                        A.insert(end(A), begin(B), end(B));
                        return A;
                    }
                }
            vector<T> eval(vector<T> x) {  // evaluate polynomial in (x1, ..., xn)
                int32_t n = x.size();
                if (is_zero()) {
                    return vector<T>(n, T(0));
                }
                vector<poly> tree(4 * n);
                build(tree, 1, begin(x), end(x));
                return eval(tree, 1, begin(x), end(x));
            }
            template <typename iter>
                poly inter(vector<poly>& tree, int32_t v, iter l, iter r, iter ly,
                        iter ry) {  // auxiliary interpolation function
                    if (r - l == 1) {
                        return {*ly / a[0]};
                    } else {
                        auto m = l + (r - l) / 2;
                        auto my = ly + (ry - ly) / 2;
                        auto A = (*this % tree[2 * v]).inter(tree, 2 * v, l, m, ly, my);
                        auto B =
                            (*this % tree[2 * v + 1]).inter(tree, 2 * v + 1, m, r, my, ry);
                        return A * tree[2 * v + 1] + B * tree[2 * v];
                    }
                }
        };
    template <typename T>
        poly<T> operator*(const T& a, const poly<T>& b) {
            return b * a;
        }

    template <typename T>
        poly<T> xk(int32_t k) {  // return x^k
            return poly<T>{1}.mul_xk(k);
        }

    template <typename T>
        T resultant(poly<T> a, poly<T> b) {  // computes resultant of a and b
            if (b.is_zero()) {
                return 0;
            } else if (b.deg() == 0) {
                return bpow(b.lead(), a.deg());
            } else {
                int32_t pw = a.deg();
                a %= b;
                pw -= a.deg();
                T mul = bpow(b.lead(), pw) * T((b.deg() & a.deg() & 1) ? -1 : 1);
                T ans = resultant(b, a);
                return ans * mul;
            }
        }
    template <typename iter>
        poly<typename iter::value_type> kmul(
                iter L, iter R) {  // computes (x-a1)(x-a2)...(x-an) without building tree
            if (R - L == 1) {
                return vector<typename iter::value_type>{-*L, 1};
            } else {
                iter M = L + (R - L) / 2;
                return kmul(L, M) * kmul(M, R);
            }
        }
    template <typename T, typename iter>
        poly<T> build(vector<poly<T>>& res, int32_t v, iter L,
                iter R) {  // builds evaluation tree for (x-a1)(x-a2)...(x-an)
            if (R - L == 1) {
                return res[v] = vector<T>{-*L, 1};
            } else {
                iter M = L + (R - L) / 2;
                return res[v] = build(res, 2 * v, L, M) * build(res, 2 * v + 1, M, R);
            }
        }
    template <typename T>
        poly<T> inter(
                vector<T> x,
                vector<T> y) {  // interpolates minimum polynomial from (xi, yi) pairs
            int32_t n = x.size();
            vector<poly<T>> tree(4 * n);
            return build(tree, 1, begin(x), end(x))
                .deriv()
                .inter(tree, 1, begin(x), end(x), begin(y), end(y));
        }
};  // namespace algebra

using namespace algebra;

const int32_t mod = 998244353;
typedef modular<mod> base;
typedef poly<base> polyn;

void solve(int case_no) {

    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    // subset x of size t - contributes 2^(n - t) to the final sum
    // sum of 2^(-size) over all solutions
    // product of (1 + x * y^(element)) - in coeff of y^s - coefficient of x = number of subsets of size 1, of x^2 = number of subsets of size 2 and so on
    // so set x = 2^(-1) in this
    // and find the product of all polynomials

    function<polyn(int, int)> multiply_many = [&] (int l, int r) {
        if (l > r) return polyn(1);
        if (l == r) {
            vector<base> w(a[l] + 1);
            w[0] = 1;
            w[a[l]] = bpow(2ll, mod - 2ll, mod * 1ll);
            return polyn(w);
        }
        int m = (l + r) >> 1;
        polyn p = multiply_many(l, m);
        polyn q = multiply_many(m + 1, r);
        p *= q;
        return p.mod_xk(s + 1);
    };

    polyn ans = multiply_many(0, n - 1);
    cout << (ans[s] * base(bpow(2ll, n * 1ll, mod * 1ll))) << '\n';
    return;
}

signed main(){
    //IOinit();
    setIO();
    //cout << setprecision(10) << fixed;
    int t = 1;
    //read_int(t);
    //cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
