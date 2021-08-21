#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

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
            get_char();
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

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        ll n, ax, bx, ay, by;
        cin >> n >> ax >> bx >> ay >> by;
        if (bx == by) {
            cout << (ax == ay) * n << '\n';
            continue;
        }
        if (bx > by) {
            swap(bx, by);
            swap(ax, ay);
        }
        ll diff = ay - ax;
        auto floor_div = [](ll x, ll y) {
            return x / y;
        };
        auto ceil_div = [](ll x, ll y) {
            return (x + y - 1) / y;
        };
        auto sum = [&floor_div](ll a, ll b, ll n) {
            ll ans = n * a;
            // [0, n)
            // [0, b), ..., [floor(n/b)*b - b, floor(n/b)*b), [floor(n/b)*b, n)
            //  0            floor(n/b) - 1                    floor(n/b)
            ll x = floor_div(n, b);
            ans += b * (x * (x - 1) / 2);
            ans += x * (n - x * b);
            return ans;
        };
        auto ans_small = [&] {
            ll n_min = floor_div((diff - 1) * bx * by, by - bx);
            ll n_max = ceil_div(diff * bx * by, by - bx);
            // [n_min, n_max)
            n_max = min(n_max, n + 1);
            n_min = max(n_min, ll(1));
            if (n_min >= n_max) return ll(0);
            ll ans = n_max - n_min +
                     (sum(ax, bx, n_max) - sum(ax, bx, n_min) -
                      sum(ay, by, n_max) + sum(ay, by, n_min));
            return ans;
        };
        auto ans_large = [&] {
            ll n_min = floor_div(diff * bx * by, by - bx);
            ll n_max = ceil_div((diff + 1) * bx * by, by - bx);
            // [n_min, n_max)
            n_max = min(n_max, n + 1);
            n_min = max(n_min, ll(1));
            if (n_min >= n_max) return ll(0);
            ll ans = n_max - n_min +
                     (-sum(ax, bx, n_max) + sum(ax, bx, n_min) +
                      sum(ay, by, n_max) - sum(ay, by, n_min));
            return ans;
        };
        ll ans = 0;
        if (diff >= 1) {
            ans = ans_small() + ans_large();
            ll collision = floor_div(diff * bx * by, by - bx);
            if (collision <= n && collision >= 1 &&
                collision * (by - bx) != diff * bx * by) {
                if (ax + floor_div(collision, bx) ==
                    ay + floor_div(collision, by)) {
                    ans--;
                }
            }
        } else if (diff == 0) {
            ans = ans_large();
        } else {
            ans = 0;
        }
        cout << ans << '\n';
    }
}

