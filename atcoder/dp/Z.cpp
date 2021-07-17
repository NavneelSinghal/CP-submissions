#ifndef DEBUG
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#endif

#include <bits/stdc++.h>

namespace IO {
    constexpr bool UNSAFE = false;
    constexpr int GLOB_BUF_SIZE = 1 << 15;
#ifndef DEBUG
    #define CHANGE_DEFAULT_STREAMS
    static struct FastInput {
        FastInput() {
            if constexpr (UNSAFE) {
                chars_read = fread(buf, 1, BUF_SIZE, in);
                buf_pos = 0;
                buf[0] = (chars_read == 0 ? -1 : buf[0]);
            }
        }
        static constexpr int BUF_SIZE = GLOB_BUF_SIZE;
        char buf[BUF_SIZE];
        size_t chars_read = 0;
        size_t buf_pos = 0;
        FILE* in = stdin;
        char cur = 0;
        inline char get_char() {
            if constexpr (!UNSAFE) {
                if (buf_pos >= chars_read) {
                    chars_read = fread(buf, 1, BUF_SIZE, in);
                    buf_pos = 0;
                    buf[0] = (chars_read == 0 ? -1 : buf[0]);
                }
            }
            return cur = buf[buf_pos++];
        }
        template <typename T>
        inline FastInput* tie(T) { return this; }
        inline void sync_with_stdio(bool) {}
        inline explicit operator bool() { return cur != -1; }
        inline static bool is_blank(char c) { return c <= ' '; }
        inline bool skip_blanks() {
            while (is_blank(cur) && cur != -1) get_char();
            return cur != -1;
        }
        inline FastInput& operator>>(char& c) {
            skip_blanks();
            c = cur;
            return *this;
        }
        inline FastInput& operator>>(std::string& s) {
            if (skip_blanks()) {
                s.clear();
                do {
                    s += cur;
                } while (!is_blank(get_char()));
            }
            return *this;
        }
        template <typename T>
        inline FastInput& read_integer(T& n) {
            // unsafe, doesn't check that characters are actually digits
            n = 0;
            if (skip_blanks()) {
                int sign = +1;
                if (cur == '-') {
                    sign = -1;
                    get_char();
                }
                do {
                    n += n + (n << 3) + cur - '0';
                } while (!is_blank(get_char()));
                n *= sign;
            }
            return *this;
        }
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value,
                                       FastInput&>::type
        operator>>(T& n) {
            return read_integer(n);
        }
    #if !defined(_WIN32) || defined(_WIN64)
        inline FastInput& operator>>(__int128& n) { return read_integer(n); }
    #endif
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value,
                                       FastInput&>::type
        operator>>(T& n) {
            // not sure if really fast, for compatibility only
            n = 0;
            if (skip_blanks()) {
                std::string s;
                (*this) >> s;
                sscanf(s.c_str(), "%lf", &n);
            }
            return *this;
        }
    } fast_input;
    #define cin IO::fast_input
    static struct FastOutput {
        static constexpr int BUF_SIZE = GLOB_BUF_SIZE;
        char buf[BUF_SIZE];
        size_t buf_pos = 0;
        static constexpr int TMP_SIZE = GLOB_BUF_SIZE;
        char tmp[TMP_SIZE];
        FILE* out = stdout;
        inline void put_char(char c) {
            buf[buf_pos++] = c;
            if (buf_pos == BUF_SIZE) {
                fwrite(buf, 1, buf_pos, out);
                buf_pos = 0;
            }
        }
        ~FastOutput() { fwrite(buf, 1, buf_pos, out); }
        inline FastOutput& operator<<(char c) {
            put_char(c);
            return *this;
        }
        inline FastOutput& operator<<(const char* s) {
            while (*s) put_char(*s++);
            return *this;
        }
        inline FastOutput& operator<<(const std::string& s) {
            for (auto x : s) put_char(x);
            return *this;
        }
        template <typename T>
        inline char* integer_to_string(T n) {
            // beware of TMP_SIZE
            char* p = tmp + TMP_SIZE - 1;
            if (n == 0)
                *--p = '0';
            else {
                bool is_negative = false;
                if (n < 0) {
                    is_negative = true;
                    n = -n;
                }
                while (n > 0) {
                    *--p = (char)('0' + n % 10);
                    n /= 10;
                }
                if (is_negative) *--p = '-';
            }
            return p;
        }
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, char*>::type
        stringify(T n) {
            return integer_to_string(n);
        }
    #if !defined(_WIN32) || defined(_WIN64)
        inline char* stringify(__int128 n) { return integer_to_string(n); }
    #endif
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value,
                                       char*>::type
        stringify(T n) {
            sprintf(tmp, "%.17f", n);
            return tmp;
        }
        template <typename T>
        inline FastOutput& operator<<(const T& n) {
            auto p = stringify(n);
            for (; *p != 0; p++) put_char(*p);
            return *this;
        }
    } fast_output;
    #define cout IO::fast_output
#endif
}  // namespace IO


using ll = int64_t;

constexpr ll inf = 1e18;
template <typename T, T x_low, T x_high, T id>
struct LiChaoTree {
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
        inline T get(T x) const { return a * x + b; }
    };

    struct Node {
        Line x;
        Node *l, *r;
        Node(const Line& x) : x{x}, l{nullptr}, r{nullptr} {}
    };

    Node* root;

    LiChaoTree() : root{nullptr} {}

    ~LiChaoTree() { cleanup(root); }

    void cleanup(Node* node) {
        if (node) cleanup(node->l), cleanup(node->r), delete node;
    }

    Node* update(Node* t, Line& x, const T& l, const T& r, const T& x_l,
                 const T& x_r) {
        if (!t) return new Node(x);
        auto t_l = t->x.get(l), t_r = t->x.get(r);
        if (t_l <= x_l && t_r <= x_r) {
            return t;
        } else if (t_l >= x_l && t_r >= x_r) {
            t = new Node(*t);
            t->x = x;
            return t;
        } else {
            T m = (l + r) / 2;
            auto t_m = t->x.get(m), x_m = x.get(m);
            t = new Node(*t);
            if (t_m > x_m) {
                std::swap(t->x, x);
                if (x_l >= t_l)
                    t->l = update(t->l, x, l, m, t_l, t_m);
                else
                    t->r = update(t->r, x, m + 1, r, t_m + x.a, t_r);
            } else {
                if (t_l >= x_l)
                    t->l = update(t->l, x, l, m, x_l, x_m);
                else
                    t->r = update(t->r, x, m + 1, r, x_m + x.a, x_r);
            }
            return t;
        }
    }

    void update(const T& a, const T& b) {
        Line x(a, b);
        root = update(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    T query(const Node* t, const T& l, const T& r, const T& x) const {
        if (!t) return id;
        if (l == r) return t->x.get(x);
        T m = (l + r) / 2;
        if (x <= m)
            return std::min(t->x.get(x), query(t->l, l, m, x));
        else
            return std::min(t->x.get(x), query(t->r, m + 1, r, x));
    }

    T query(const T& x) const { return query(root, x_low, x_high, x); }
};

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        ll C;
        cin >> C;
        vector<ll> h(n);
        for (auto& x : h) cin >> x;
        // cost = hj^2 + hi^2 - 2 * hi * hj + C
        vector<ll> dp(n);
        dp[0] = 0;
        LiChaoTree<int64_t, int64_t(0), int64_t(1e6), int64_t(1e18)> lichao;
        lichao.update(-2 * h[0], h[0] * h[0]);
        for (int i = 1; i < n; ++i) {
            dp[i] = C + h[i] * h[i] + lichao.query(h[i]);
            lichao.update(-2 * h[i], h[i] * h[i] + dp[i]);
        }
        cout << dp[n - 1] << '\n';
    }
}