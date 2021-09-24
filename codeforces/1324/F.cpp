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

using namespace std;

template <class Aggregate, class Value, class MergeInto, class MergeInverse>
auto exclusive_with_inverse(const std::basic_string<Value>& a,
                            const Aggregate& base, const MergeInto& merge_into,
                            const MergeInverse& merge_inv, int vertex) {
    int n = (int)std::size(a);
    Aggregate all = base;
    for (int i = 0; i < n; ++i) all = merge_into(all, a[i]);
    std::basic_string<Aggregate> b(n, all);
    for (int i = 0; i < n; ++i) b[i] = merge_inv(b[i], a[i]);
    return b;
}

// MergeInto : Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
// Base : Vertex(int) -> Aggregate
// FinalizeMerge : Aggregate * Vertex(int) -> Value

// MergeInto -> merge the value corresponding to a child into the aggregate
// FinalizeMerge -> finalize the merge (update the vertex with child aggregates)
template <class Aggregate, class Value, class MergeInto, class FinalizeMerge,
          class Base, class MergeInverse = std::nullptr_t>
auto rerooter(const std::vector<std::basic_string<int>>& g,
              const Value& default_val, const Aggregate&, const Base& base,
              const MergeInto& merge_into, const FinalizeMerge& finalize_merge,
              const MergeInverse& merge_inv = nullptr) {
    static_assert(!std::is_same_v<MergeInverse, std::nullptr_t>);
    int n = (int)std::size(g);

    std::vector<Value> root_dp(n, default_val);
    std::vector<Value> dp(n, default_val);

    std::vector<int> bfs(n), parent(n, -1);
    int cnt = 1;
    parent[0] = 0;
    for (int i = 0; i < n; ++i) {
        int u = bfs[i];
        for (auto v : g[u]) {
            if (parent[v] != -1) continue;
            parent[v] = u;
            bfs[cnt++] = v;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int u = bfs[i];
        int edge_index = -1;
        int p = parent[u];
        Aggregate aggregate = base(u);
        for (auto v : g[u]) {
            ++edge_index;
            if (v == p) continue;
            aggregate = merge_into(aggregate, dp[v]);
        }
        dp[u] = finalize_merge(aggregate, u);
    }

    for (auto u : bfs) {
        dp[parent[u]] = dp[u];
        std::basic_string<Aggregate> edge_dp;
        for (auto v : g[u]) edge_dp += dp[v];
        std::basic_string<Aggregate> dp_exclusive;
        dp_exclusive =
            exclusive_with_inverse(edge_dp, base(u), merge_into, merge_inv, u);
        int sz = (int)g[u].size();
        auto& gu = g[u];
        for (int i = 0; i < sz; ++i)
            dp[gu[i]] = finalize_merge(dp_exclusive[i], u);
        root_dp[u] = finalize_merge(merge_into(dp_exclusive[0], edge_dp[0]), u);
    }

    return root_dp;
}

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
    auto merge_into = [](int vertex_dp, int neighbor_dp) {
        return vertex_dp + max(0, neighbor_dp);
    };
    auto finalize_merge = [&color](int vertex_dp, int vertex) {
        return vertex_dp + 2 * color[vertex] - 1;
    };
    auto base = [](int) {
        return 0;
    };
    auto merge_inv = [](int vertex_dp, int neighbor_dp) {
        return vertex_dp - max(0, neighbor_dp);
    };
    auto root_dp =
        rerooter(g, 0, 0, base, merge_into, finalize_merge, merge_inv);
    for (auto& x : root_dp) cout << x << ' ';
    cout << '\n';
}

