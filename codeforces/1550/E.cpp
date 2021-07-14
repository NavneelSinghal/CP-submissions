#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

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

using namespace std;
using ll = int64_t;

template <class T, bool unsafe = false>
constexpr uint32_t ctz(T a) {
    if constexpr (!unsafe) {
        if (!a) return sizeof(T) * 8;
    }
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return (uint32_t)(__builtin_ctz((uint32_t)a));
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return (uint32_t)(__builtin_ctzll((uint64_t)a));
    } else {
        static_assert(sizeof(T) == sizeof(uint64_t) * 2);
        uint32_t l = ctz((uint64_t)a);
        return l != sizeof(uint64_t) * 8
                   ? l
                   : l + ctz((uint64_t)(a >> sizeof(uint64_t) * 8));
    }
}

template <class T, bool unsafe = false>
constexpr uint32_t clz(T a) {
    if constexpr (!unsafe) {
        if (!a) return sizeof(T) * 8;
    }
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return (uint32_t)(__builtin_clz((uint32_t)a));
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return (uint32_t)(__builtin_clzll((uint64_t)a));
    } else {
        static_assert(sizeof(T) == sizeof(uint64_t) * 2);
        uint32_t l = clz((uint64_t)(a >> sizeof(uint64_t) * 8));
        return l != sizeof(uint64_t) * 8 ? l : l + clz((uint64_t)a);
    }
}

// -1 for 0
template <class T, bool unsafe = false>
constexpr uint32_t lg(T a) {
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return sizeof(uint32_t) * 8 - 1 - clz<T, unsafe>(a);
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return sizeof(uint64_t) * 8 - 1 - clz<T, unsafe>(a);
    } else {
        return sizeof(uint64_t) * 16 - 1 - clz<T, unsafe>(a);
    }
}

// split [l, r]
template <class Integer, class Predicate, bool type>
// __attribute__((target("bmi")))
Integer find_bin_split(Integer l, Integer r, const Predicate &pred) {
    if (l > r) {
        if constexpr (type)
            return r;
        else
            return r + 1;
    }
    ++r;
    Integer w = Integer(1) << lg<Integer, true>(r - l);
    --l;
    if (pred(l + w)) l = r - w;
    for (w >>= 1; w >= Integer(1); w >>= 1)
        if (pred(l + w)) l += w;
    if constexpr (type)
        return l;
    else
        return l + 1;
}

template <class Integer, class Predicate>
Integer find_first_false(Integer l, Integer r, const Predicate &pred) {
    return find_bin_split<Integer, Predicate, false>(l, r, pred);
}

template <class Integer, class Predicate>
Integer find_last_true(Integer l, Integer r, const Predicate &pred) {
    return find_bin_split<Integer, Predicate, true>(l, r, pred);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << find_last_true(1, n / k, [&](int m) {
            const int inf = 1e9;
            vector<vector<int>> leftmost(k, vector<int>(n + 1, inf));
            for (int bit = 0; bit < k; ++bit) {
                int prv = n;
                for (int i = n - 1; i >= 0; --i) {
                    leftmost[bit][i] = leftmost[bit][i + 1];
                    if (s[i] != '?' && s[i] != 'a' + bit) prv = i;
                    if (prv >= i + m) leftmost[bit][i] = i;
                }
            }
            vector<int> dp(1 << k, inf);
            dp[0] = 0;
            for (int mask = 0; mask < (1 << k); ++mask) {
                if (dp[mask] >= n) continue;
                for (int bit = 0; bit < k; ++bit)
                    if (!((mask >> bit) & 1))
                        dp[mask ^ (1 << bit)] = min(
                            dp[mask ^ (1 << bit)], leftmost[bit][dp[mask]] + m);
            }
            return dp[(1 << k) - 1] <= n;
        }) << '\n';
    }
}
