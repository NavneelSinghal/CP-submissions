#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

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
        inline FastInput* tie(T) {
            return this;
        }
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

template <class Node, class AL, class AR, class EL, class ER, class Compute>
struct Mo {
   private:
    std::vector<Node> ans;
    Node id_node;
    AL add_left;
    AR add_right;
    EL erase_left;
    ER erase_right;
    Compute compute;
    struct Query {
        int l, r;
        int64_t order;
        Query() {}
        inline int64_t hilbert_order(int x, int y, int p, int to_rotate) {
            if (p == 0) return 0;
            static constexpr int rotate_delta[4] = {3, 0, 0, 1};
            int hp = 1 << (p - 1);
            int seg = (x < hp) ? ((y < hp) ? 0 : 3) : ((y < hp) ? 1 : 2);
            seg = (seg + to_rotate) & 3;
            int nx = x & (x ^ hp), ny = y & (y ^ hp);
            int nrot = (to_rotate + rotate_delta[seg]) & 3;
            int64_t sub_square_size = int64_t(1) << (2 * p - 2);
            int64_t ans = seg * sub_square_size;
            int64_t add = hilbert_order(nx, ny, p - 1, nrot);
            ans += (seg == 1 || seg == 2) ? add : (sub_square_size - add - 1);
            return ans;
        }
        Query(int _l, int _r, int lgn) : l(_l), r(_r) {
            order = hilbert_order(_l, _r, lgn, 0);
        }
        bool operator<(const Query& q) const { return order < q.order; }
    };
    template <class T, bool unsafe = false>
    __attribute__((target("bmi,bmi2,popcnt,lzcnt"))) constexpr uint32_t clz(
        T a) {
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
    template <class T, bool unsafe = false>
    __attribute__((target("bmi,bmi2,popcnt,lzcnt"))) constexpr uint32_t lg(
        T a) {
        if constexpr (sizeof(T) <= sizeof(uint32_t)) {
            return sizeof(uint32_t) * 8 - 1 - clz<T, unsafe>(a);
        } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
            return sizeof(uint64_t) * 8 - 1 - clz<T, unsafe>(a);
        } else {
            return sizeof(uint64_t) * 16 - 1 - clz<T, unsafe>(a);
        }
    }

   public:
    Mo(int _n, const std::vector<std::pair<int, int>>& _queries,
       const Node& _id_node, const AL& _add_left, const AR& _add_right,
       const EL& _erase_left, const ER& _erase_right, const Compute& _compute)
        : ans(_queries.size()),
          id_node(_id_node),
          add_left(_add_left),
          add_right(_add_right),
          erase_left(_erase_left),
          erase_right(_erase_right),
          compute(_compute) {
        int q = (int)_queries.size();
        int n = _n;
        std::vector<Query> queries;
        queries.reserve(q);
        int lgn = lg(2 * n - 1);
        for (int i = 0; i < q; ++i) {
            auto [l, r] = _queries[i];
            queries.push_back(Query(l, r, lgn));
        }
        std::vector<int> id(q);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(),
                  [&queries](int i, int j) { return queries[i] < queries[j]; });
        int l = 0, r = -1;
        Node cur = id_node;
        for (auto i : id) {
            auto [ql, qr, _] = queries[i];
            while (l > ql) add_left(--l, cur);
            while (r < qr) add_right(++r, cur);
            while (l < ql) erase_left(l++, cur);
            while (r > qr) erase_right(r--, cur);
            ans[i] = compute(cur);
        }
    }
    std::vector<Node> get() { return ans; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;

        int q;
        cin >> q;
        vector<pair<int, int>> queries;
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            queries.emplace_back(l, r);
        }

        constexpr int block_sz = 800;
        const int A = *max_element(begin(a), end(a));

        vector<int> type(A + 1), active(A + 1), active_in_block(block_sz);
        int total_unique = 0;

        using Node = int;

        auto add_left = [&](int i, Node x) {
            auto ai = a[i];
            ++type[ai];
            if (type[ai] == 1) {
                ++active[ai];
                ++active_in_block[ai / block_sz];
                ++total_unique;
            } else if (type[ai] == 2) {
                --active[ai];
                --active_in_block[ai / block_sz];
                --total_unique;
            }
        };

        auto add_right = add_left;

        auto erase_left = [&](int i, Node x) {
            auto ai = a[i];
            --type[ai];
            if (type[ai] == 0) {
                --active[ai];
                --active_in_block[ai / block_sz];
                --total_unique;
            } else if (type[ai] == 1) {
                ++active[ai];
                ++active_in_block[ai / block_sz];
                ++total_unique;
            }
        };

        auto erase_right = erase_left;

        auto compute = [&](Node x) {
            if (total_unique == 0) return 0;
            for (int i = 0; i < block_sz; ++i)
                if (active_in_block[i] > 0)
                    for (int j = i * block_sz;; ++j)
                        if (active[j]) return j;
            return 0;
        };

        Mo mo(n, queries, 0, add_left, add_right, erase_left, erase_right,
              compute);

        for (auto x : mo.get()) cout << x << '\n';
    }
}

