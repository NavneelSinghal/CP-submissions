#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ld = long double;

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

// Fold : Aggregate * Arg * Vertex(int) * EdgeIndex(int) -> Aggregate
template <class Aggregate, class Arg, class Fold>
auto exclusive(const std::basic_string<Arg>& a, const Aggregate& base,
               Fold fold, int vertex) {
    int n = (int)std::size(a);
    std::vector<Aggregate> b(n, base);
    for (int bit = (int)std::__lg(n); bit >= 0; --bit) {
        for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
        int sz = n - (n & !bit);
        for (int i = 0; i < sz; ++i) {
            int index = (i >> bit) ^ 1;
            b[index] = fold(b[index], a[i], vertex, i);
        }
    }
    return b;
}

// Fold : Aggregate * Arg * Vertex(int) * EdgeIndex(int) -> Aggregate
template <class Arg, class Aggregate, class Fold, class CombineWithRoot>
auto rerooter(const std::vector<std::basic_string<int>>& g, const Arg& arg_base,
              const std::vector<Aggregate>& base, Fold fold,
              CombineWithRoot combine_with_root) {
    int n = (int)std::size(g);

    std::vector<Arg> root_dp(n, arg_base);
    std::vector<std::basic_string<Arg>> edge_dp(n);

    std::vector<Arg> dp(n, arg_base);

    const auto dfs_compute = [&](auto self, int u, int p) -> void {
        Aggregate aggregate = base[u];
        int edge_index = -1;
        for (auto v : g[u]) {
            edge_index++;
            if (v == p) continue;
            self(self, v, u);
            aggregate = fold(aggregate, dp[v], u, edge_index);
        }
        dp[u] = combine_with_root(aggregate, u);
    };

    dfs_compute(dfs_compute, 0, -1);

    const auto dfs_reroot = [&](auto self, int u, int p) -> void {
        dp[p] = dp[u];
        edge_dp[u].reserve(g[u].size());
        for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
        auto dp_exclusive = exclusive(edge_dp[u], base[u], fold, u);
        for (int i = 0; i < (int)dp_exclusive.size(); ++i) {
            auto v = g[u][i];
            dp[v] = combine_with_root(dp_exclusive[i], u);
        }
        root_dp[u] =
            combine_with_root(fold(dp_exclusive[0], edge_dp[u][0], u, 0), u);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };

    dfs_reroot(dfs_reroot, 0, 0);

    return make_pair(root_dp, edge_dp);
}

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    std::vector<int> color(n);
    for (auto& x : color) cin >> x;
    std::vector<std::basic_string<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    using Arg = int;
    using Aggregate = int;
    auto fold = [](Aggregate vertex_dp, Arg neighbor_dp, int vertex,
                   int edge_index) -> Aggregate {
        return Aggregate{vertex_dp + max(0, neighbor_dp)};
    };
    auto combine_with_root = [&color](Aggregate vertex_dp, int vertex) -> Arg {
        return Arg{vertex_dp + 2 * color[vertex] - 1};
    };
    auto [root_dp, edge_dp] =
        rerooter(g, Arg{0}, std::vector<Aggregate>(n, Aggregate{0}), fold,
                 combine_with_root);
    for (auto& x : root_dp) cout << x << ' ';
    cout << '\n';
}

