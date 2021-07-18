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

struct DSURollbacks {
   private:
    // negative - size; happens at the root
    // non-negative - parent; happens at non-root
    std::vector<int> parent_or_size;
    std::vector<std::array<int, 4>> history;
    static constexpr int inf = 1e9;

   public:
    DSURollbacks(int n) : parent_or_size(n, -1) {}
    int root(int v) {
        if (parent_or_size[v] < 0) return v;
        return root(parent_or_size[v]);
    }
    bool join(int u, int v) {
        u = root(u);
        v = root(v);
        if (u == v) {
            history.emplace_back(std::array{inf, inf, inf, inf});
            return false;
        } else {
            if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);
            history.emplace_back(std::array{u, v, parent_or_size[u], parent_or_size[v]});
            parent_or_size[u] += parent_or_size[v];
            parent_or_size[v] = u;
            return true;
        }
    }
    void rollback() {
        auto [u, v, psu, psv] = history.back();
        history.pop_back();
        if (u != inf) parent_or_size[u] = psu, parent_or_size[v] = psv;
    }
};

struct edge {
    int u, v;
    int w;
    bool operator<(const edge& e) { return w < e.w; }
};

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, m;
        cin >> n >> m;
        DSURollbacks dsu(n);
        vector<edge> edges(m);
        int maxw = 0;
        for (auto& [u, v, w] : edges)
            cin >> u >> v >> w, --u, --v, maxw = max(w, maxw);
        maxw++;
        vector<vector<edge>> g(maxw);
        for (auto& [u, v, w] : edges) g[w].push_back({u, v, w});
        vector<vector<vector<pair<edge, int>>>> queries(maxw);
        auto sorted_edges = edges;
        sort(begin(sorted_edges), end(sorted_edges));
        int q;
        cin >> q;
        vector<int> works(q, 1);
        for (int i = 0; i < q; ++i) {
            int sz;
            cin >> sz;
            vector<int> edge_ids(sz);
            for (auto& x : edge_ids) cin >> x, --x;
            sort(begin(edge_ids), end(edge_ids),
                 [&](int i, int j) { return edges[i] < edges[j]; });
            for (auto edge_id : edge_ids) {
                auto edge = edges[edge_id];
                if (queries[edge.w].empty() ||
                    queries[edge.w].back().back().second != i)
                    queries[edge.w].emplace_back();
                queries[edge.w].back().emplace_back(edge, i);
            }
        }
        for (int w = 1; w < maxw; ++w) {
            for (auto& x : queries[w]) {
                for (auto& [edge, query_index] : x) {
                    auto [u, v, w] = edge;
                    if (!dsu.join(u, v)) works[query_index] = false;
                }
                for (int i = 0; i < (int)x.size(); ++i) dsu.rollback();
            }
            for (auto& [u, v, w] : g[w]) dsu.join(u, v);
        }
        for (int i = 0; i < q; ++i) {
            cout << (works[i] ? "YES" : "NO") << '\n';
        }
    }
}
