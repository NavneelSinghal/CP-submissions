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

#define int long long
#define double long double
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

using mint = Modular<>;
//using mint = Modular<Mod>;

const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size() == 0) return;
    FILE* fin = freopen((name+".in").c_str(), "r", stdin);
    FILE* fout = freopen((name+".out").c_str(), "w", stdout);
    cout << setprecision(10) << fixed;
}
// matrix library

template <typename T>
struct Matrix {
    
    int32_t rows, cols;
    vector<vector<T>> mat;
    
    // rows and columns
    Matrix(int32_t r, int32_t c) : rows(r), cols(c), mat(vector<vector<T>>(r, vector<T>(c))) {};
    
    // initializer list
    Matrix(initializer_list<initializer_list<T>> l) : rows(l.size()), cols(l.begin()->size()) {
        mat = vector<vector<T>>(rows);
        int i = 0;
        for (auto &x : l) {
            mat[i] = x;
            ++i;
            assert(x.size() == cols);
        }
    };
    
    void fill(T val) {
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < cols; j++) {
                mat[i][j] = val;
            }
        }
    }
    
    void reset() { fill(0); }
    
    void setid() {
        assert(rows == cols);
        for (int32_t i = 0; i < rows; i++) {
            mat[i][i] = 1;
        }
    }
    
    static Matrix id(int32_t n) {
        Matrix m(n, n);
        m.setid();
        return m;
    }
    
    Matrix operator + (const Matrix& a) const {
        assert(rows == a.rows && cols == a.cols);
        Matrix<T> res(rows, cols);
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < cols; j++) {
                res.mat[i][j] = mat[i][j] + a.mat[i][j];
            }
        }
    }
    
    Matrix<T> operator * (const Matrix<T>& a) const {
        assert(cols == a.rows);
        Matrix<T> res(rows, a.cols);
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < a.cols; j++) {
                res.mat[i][j] = 0;
                for (int32_t k = 0; k < cols; k++) {
                    res.mat[i][j] += mat[i][k] * a.mat[k][j];
                }
            }
        }
        return res;
    }
    
    void operator += (const Matrix& a) { *this = *this + a; }
    void operator *= (const Matrix& a) { *this = *this * a; }

    Matrix<T> operator ^ (int32_t n) {
        Matrix<T> ans(rows, cols);
        ans.setid();
        Matrix<T> a = *this;
        while (n) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
};

using node = pair<pii, pii>;

const node ID = mp(mp(LINF, -LINF), mp(LINF, -LINF));
node t[4 * maxn];

node combine(node pl, node pr) {
    int mne = min({pl.S.F, pr.S.F, pl.F.F - pr.F.S, pl.S.F + pr.S.F});
    int mxe = max({pl.S.S, pr.S.S, pl.F.S - pr.F.F, pr.S.S + pl.S.S});
    int mno = min({pl.F.F, pr.F.F, pl.F.F - pr.S.S, pl.S.F + pr.F.F});
    int mxo = max({pl.F.S, pr.F.S, pl.F.S - pr.S.F, pl.S.S + pr.F.S});
    return mp(mp(mno, mxo), mp(mne, mxe));
}

node make_node(int val) {
    return mp(mp(val, val), mp(LINF, -LINF));
}

void build(int v, int l, int r, vector<int>& a) {
    if (l == r) {
        t[v] = make_node(a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid, a);
    build((v << 1) | 1, mid + 1, r, a);
    t[v] = combine(t[(v << 1)], t[(v << 1) | 1]);
}

void update(int v, int l, int r, int idx, int val) {
    if (l == r) {
        t[v] = make_node(val);
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid)
        update(v << 1, l, mid, idx, val);
    else
        update((v << 1) | 1, mid + 1, r, idx, val);
    t[v] = combine(t[v << 1], t[(v << 1) | 1]);
}

node query(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) >> 1;
    if (l > tm) return query((v << 1) | 1, tm + 1, tr, l, r);
    if (tm + 1 > r) return query(v << 1, tl, tm, l, r);
    return combine(query(v << 1, tl, tm, l, tm),
                   query((v << 1) | 1, tm + 1, tr, tm + 1, r));
}

void solve(int case_no) {
    int n, q;
    cin >> n >> q;
    vi a(n);
    rep(i, n) cin >> a[i];
    build(1, 0, n - 1, a);
    auto ans = query(1, 0, n - 1, 0, n - 1);
    assert(ans.F.S != LINF);
    assert(ans.S.S != LINF);
    cout << max(ans.F.S, ans.S.S) << '\n';
    rep(_, q) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        update(1, 0, n - 1, l, a[r]);
        update(1, 0, n - 1, r, a[l]);
        swap(a[l], a[r]);
        auto ans = query(1, 0, n - 1, 0, n - 1);
        assert(ans.F.S != LINF);
        assert(ans.S.S != LINF);
        cout << max(ans.F.S, ans.S.S) << '\n';
    }
}

signed main(){
    //IOinit();
    setIO();
    int t = 1;
    //read_int(t);
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
