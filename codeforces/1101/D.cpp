#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

struct IOPre {
    static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;
    std::array<char, 4 * SZ> num;
    constexpr IOPre() : num{} {
        for (int i = 0; i < SZ; i++) {
            int n = i;
            for (int j = 3; j >= 0; j--) {
                num[i * 4 + j] = static_cast<char>(n % TEN + '0');
                n /= TEN;
            }
        }
    }
};
struct IO {
#if !HAVE_DECL_FREAD_UNLOCKED
    #define fread_unlocked fread
#endif
#if !HAVE_DECL_FWRITE_UNLOCKED
    #define fwrite_unlocked fwrite
#endif
    static constexpr int SZ = 1 << 17, LEN = 32, TEN = 10, HUNDRED = TEN * TEN,
                         THOUSAND = HUNDRED * TEN, TENTHOUSAND = THOUSAND * TEN,
                         MAGIC_MULTIPLY = 205, MAGIC_SHIFT = 11, MASK = 15,
                         TWELVE = 12, SIXTEEN = 16;
    static constexpr IOPre io_pre = {};
    std::array<char, SZ> input_buffer, output_buffer;
    int input_ptr_left, input_ptr_right, output_ptr_right;

    IO()
        : input_buffer{},
          output_buffer{},
          input_ptr_left{},
          input_ptr_right{},
          output_ptr_right{} {}
    IO(const IO&) = delete;
    IO(IO&&) = delete;
    IO& operator=(const IO&) = delete;
    IO& operator=(IO&&) = delete;

    ~IO() {
        flush();
    }

    template <class T>
    struct is_char {
        static constexpr bool value = std::is_same_v<T, char>;
    };

    template <class T>
    struct is_bool {
        static constexpr bool value = std::is_same_v<T, bool>;
    };

    template <class T>
    struct is_string {
        static constexpr bool value =
            std::is_same_v<T, std::string> || std::is_same_v<T, const char*> ||
            std::is_same_v<T, char*> || std::is_same_v<std::decay_t<T>, char*>;
    };

    template <class T, class D = void>
    struct is_custom {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_custom<T, std::void_t<typename T::internal_value_type>> {
        static constexpr bool value = true;
    };

    template <class T>
    struct is_default {
        static constexpr bool value = is_char<T>::value || is_bool<T>::value ||
                                      is_string<T>::value ||
                                      std::is_integral_v<T>;
    };

    template <class T, class D = void>
    struct is_iterable {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_iterable<
        T, typename std::void_t<decltype(std::begin(std::declval<T>()))>> {
        static constexpr bool value = true;
    };

    template <class T, class D = void, class E = void>
    struct is_applyable {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_applyable<T, std::void_t<typename std::tuple_size<T>::type>,
                        std::void_t<decltype(std::get<0>(std::declval<T>()))>> {
        static constexpr bool value = true;
    };

    template <class T>
    static constexpr bool needs_newline = (is_iterable<T>::value ||
                                           is_applyable<T>::value) &&
                                          (!is_default<T>::value);

    template <typename T, typename U>
    struct any_needs_newline {
        static constexpr bool value = false;
    };
    template <typename T>
    struct any_needs_newline<T, std::index_sequence<>> {
        static constexpr bool value = false;
    };
    template <typename T, std::size_t I, std::size_t... Is>
    struct any_needs_newline<T, std::index_sequence<I, Is...>> {
        static constexpr bool value =
            needs_newline<decltype(std::get<I>(std::declval<T>()))> ||
            any_needs_newline<T, std::index_sequence<Is...>>::value;
    };

    inline void load() {
        memmove(std::begin(input_buffer),
                std::begin(input_buffer) + input_ptr_left,
                input_ptr_right - input_ptr_left);
        input_ptr_right =
            input_ptr_right - input_ptr_left +
            static_cast<int>(fread_unlocked(
                std::begin(input_buffer) + input_ptr_right - input_ptr_left, 1,
                SZ - input_ptr_right + input_ptr_left, stdin));
        input_ptr_left = 0;
    }

    inline void read_char(char& c) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        c = input_buffer[input_ptr_left++];
    }
    inline void read_string(std::string& x) {
        char c;
        while (read_char(c), c < '!') continue;
        x = c;
        while (read_char(c), c >= '!') x += c;
    }
    template <class T>
    inline std::enable_if_t<std::is_integral_v<T>, void> read_int(T& x) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        char c = 0;
        do c = input_buffer[input_ptr_left++];
        while (c < '-');
        [[maybe_unused]] bool minus = false;
        if constexpr (std::is_signed<T>::value == true)
            if (c == '-') minus = true, c = input_buffer[input_ptr_left++];
        x = 0;
        while (c >= '0')
            x = x * TEN + (c & MASK), c = input_buffer[input_ptr_left++];
        if constexpr (std::is_signed<T>::value == true)
            if (minus) x = -x;
    }

    inline void skip_space() {
        if (input_ptr_left + LEN > input_ptr_right) load();
        while (input_buffer[input_ptr_left] <= ' ') input_ptr_left++;
    }

    inline void flush() {
        fwrite_unlocked(std::begin(output_buffer), 1, output_ptr_right, stdout);
        output_ptr_right = 0;
    }

    inline void write_char(char c) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = c;
    }

    inline void write_bool(bool b) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = b ? '1' : '0';
    }

    inline void write_string(const std::string& s) {
        for (auto x : s) write_char(x);
    }

    inline void write_string(const char* s) {
        while (*s) write_char(*s++);
    }

    inline void write_string(char* s) {
        while (*s) write_char(*s++);
    }

    template <typename T>
    inline std::enable_if_t<std::is_integral_v<T>, void> write_int(T x) {
        if (output_ptr_right > SZ - LEN) flush();
        if (!x) {
            output_buffer[output_ptr_right++] = '0';
            return;
        }
        if constexpr (std::is_signed<T>::value == true)
            if (x < 0) output_buffer[output_ptr_right++] = '-', x = -x;
        int i = TWELVE;
        std::array<char, SIXTEEN> buf{};
        while (x >= TENTHOUSAND) {
            memcpy(std::begin(buf) + i,
                   std::begin(io_pre.num) + (x % TENTHOUSAND) * 4, 4);
            x /= TENTHOUSAND;
            i -= 4;
        }
        if (x < HUNDRED) {
            if (x < TEN) {
                output_buffer[output_ptr_right++] = static_cast<char>('0' + x);
            } else {
                std::uint32_t q =
                    (static_cast<std::uint32_t>(x) * MAGIC_MULTIPLY) >>
                    MAGIC_SHIFT;
                std::uint32_t r = static_cast<std::uint32_t>(x) - q * TEN;
                output_buffer[output_ptr_right] = static_cast<char>('0' + q);
                output_buffer[output_ptr_right + 1] =
                    static_cast<char>('0' + r);
                output_ptr_right += 2;
            }
        } else {
            if (x < THOUSAND) {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2) + 1, 3),
                    output_ptr_right += 3;
            } else {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2), 4),
                    output_ptr_right += 4;
            }
        }
        memcpy(std::begin(output_buffer) + output_ptr_right,
               std::begin(buf) + i + 4, TWELVE - i);
        output_ptr_right += TWELVE - i;
    }
    template <typename T_>
    IO& operator<<(T_&& x) {
        using T = typename std::remove_cv<
            typename std::remove_reference<T_>::type>::type;
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        if constexpr (is_custom<T>::value) {
            write_int(x.get());
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_bool<T>::value) {
                write_bool(x);
            } else if constexpr (is_string<T>::value) {
                write_string(x);
            } else if constexpr (is_char<T>::value) {
                write_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                write_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            // strings are immune
            using E = decltype(*std::begin(x));
            constexpr char sep = needs_newline<E> ? '\n' : ' ';
            int i = 0;
            for (const auto& y : x) {
                if (i++) write_char(sep);
                operator<<(y);
            }
        } else if constexpr (is_applyable<T>::value) {
            // strings are immune
            constexpr char sep =
                (any_needs_newline<
                    T, std::make_index_sequence<std::tuple_size_v<T>>>::value)
                    ? '\n'
                    : ' ';
            int i = 0;
            std::apply(
                [this, &sep, &i](auto const&... y) {
                    (((i++ ? write_char(sep) : void()), this->operator<<(y)),
                     ...);
                },
                x);
        }
        return *this;
    }
    template <typename T>
    IO& operator>>(T& x) {
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        static_assert(!is_bool<T>::value);
        if constexpr (is_custom<T>::value) {
            typename T::internal_value_type y;
            read_int(y);
            x = y;
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_string<T>::value) {
                read_string(x);
            } else if constexpr (is_char<T>::value) {
                read_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                read_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            for (auto& y : x) operator>>(y);
        } else if constexpr (is_applyable<T>::value) {
            std::apply([this](auto&... y) { ((this->operator>>(y)), ...); }, x);
        }
        return *this;
    }

    IO* tie(std::nullptr_t) {
        return this;
    }
    void sync_with_stdio(bool) {}
};
IO io;
#define cin io
#define cout io

using namespace std;

template <int n = 1'000'000>
struct fast_sieve_func_spf {
    vector<int> primes, spf;
    vector<char> is_prime;
    fast_sieve_func_spf() {
        is_prime.assign(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        spf.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) primes.push_back(i), spf[i] = i;
            int spfi = spf[i];
            for (const auto p : primes) {
                const int k = i * p;
                if (k > n) break;
                is_prime[k] = false;
                spf[k] = p;
                if (spfi == p) break;
            }
        }
    }
};

fast_sieve_func_spf<200000> sv{};

namespace graph_representations {
    template <typename Data>
    struct edge_data {
        int to, nxt;
        Data d;
        constexpr edge_data() : to{}, nxt{}, d{} {}
        constexpr edge_data(int to_, int nxt_, Data d_)
            : to{to_}, nxt{nxt_}, d{d_} {}
    };
    struct edge {
        int to, nxt;
        constexpr edge() : to{}, nxt{} {}
        constexpr edge(int to_, int nxt_) : to{to_}, nxt{nxt_} {}
    };
    template <typename Data, int N, int M>
    struct graph {
        static constexpr bool has_data = !std::is_same_v<Data, void>;
        using edge_t = std::conditional_t<has_data, edge_data<Data>, edge>;
        constexpr graph() : cur_edges{} { head.fill(-1); }
        void clear(int n = N) {
            std::fill_n(std::begin(head), n, -1);
            cur_edges = 0;
        }
        void clear_vertex(int u) { head[u] = -1; }
        void clear_edges() { cur_edges = 0; }
        template <class T>
        void add_edge(int u, int v, T d) noexcept {
            if constexpr (has_data) {
                edges[cur_edges] = {v, head[u], d};
            } else {
                throw "Graph doesn't handle edge data, do not use add_edge with data";
            }
            head[u] = cur_edges++;
        }
        void add_edge(int u, int v) noexcept {
            if constexpr (has_data) {
                throw "Graph handles edge data, do not use add_edge without data";
            } else {
                edges[cur_edges] = {v, head[u]};
            }
            head[u] = cur_edges++;
        }
        struct edge_range {
            const edge_t* edges_array;
            const int start;
            struct edge_iterator {
                const edge_t* const edges_array;
                int edge_index;
                explicit constexpr edge_iterator(const edge_t* edges_array_,
                                                 const int edge_index_)
                    : edges_array{edges_array_}, edge_index{edge_index_} {}
                constexpr const edge_iterator& operator++() {
                    edge_index = edges_array[edge_index].nxt;
                    return *this;
                }
                constexpr const edge_iterator operator++(int) {
                    auto temp = *this;
                    return operator++(), temp;
                }
                constexpr auto operator*() const {
                    if constexpr (has_data) {
                        return std::pair{edges_array[edge_index].to,
                                         edges_array[edge_index].d};
                    } else {
                        return edges_array[edge_index].to;
                    }
                }
                constexpr bool operator!=(const edge_iterator& it) const {
                    return edge_index != it.edge_index;
                }
                constexpr bool operator==(const edge_iterator& it) const {
                    return edge_index == it.edge_index;
                }
            };
            constexpr edge_iterator begin() {
                return edge_iterator(edges_array, start);
            }
            constexpr edge_iterator end() {
                return edge_iterator(edges_array, -1);
            }
            constexpr edge_iterator begin() const {
                return edge_iterator(edges_array, start);
            }
            constexpr edge_iterator end() const {
                return edge_iterator(edges_array, -1);
            }
        };
        edge_range operator[](int u) {
            return edge_range{edges.data(), head[u]};
        }
        edge_range operator[](int u) const {
            return edge_range{edges.data(), head[u]};
        }

       private:
        std::array<int, N> head;
        std::array<edge_t, M> edges;
        int cur_edges;
    };
}  // namespace graph_representations

template <typename Data, int N, int M>
using fixed_size_graph_with_data_t = graph_representations::graph<Data, N, M>;
template <int N, int M>
using fixed_size_graph_t = graph_representations::graph<void, N, M>;

struct Pair {
    int first, second;
};
static constexpr int N = 200000;
bitset<N + 1> used, visited_1, visited_2;

fixed_size_graph_with_data_t<int, N + 1, 6 * N> edges;
fixed_size_graph_t<N, 2 * N - 2> g;

int all[N], allptr = 0;
pair<int, int> q[N];
int q_start, q_end;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    bool no_add = all_of(a.begin(), a.end(), [](int x) { return x == 1; });
    if (no_add) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        int G = gcd(a[u], a[v]);
        while (G > 1) {
            int p = sv.spf[G];
            edges.add_edge(p, u, v);
            while (G % p == 0) G /= p;
        }
    }
    int ans = 0;
    for (int i = 2; i <= N; ++i) {
        for (auto [u, v] : edges[i]) {
            g.add_edge(u, v);
            g.add_edge(v, u);
            if (!used[u]) used.set(u), all[allptr++] = u;
            if (!used[v]) used.set(v), all[allptr++] = v;
        }
        if (allptr == 0) continue;
        for (int j = 0; j < allptr; ++j) {
            int root = all[j];
            if (visited_2[root]) continue;
            pair<int, int> best{0, root};
            q_start = 0, q_end = -1;
            q[++q_end] = {0, root};
            visited_1.set(root);
            while (q_start <= q_end) {
                auto [du, u] = q[q_start++];
                for (auto v : g[u]) {
                    if (visited_1[v]) continue;
                    visited_1.set(v);
                    pair x{du + 1, v};
                    best = max(best, x);
                    q[++q_end] = x;
                }
            }
            root = best.second;
            best = {0, root};
            q_start = 0, q_end = -1;
            q[++q_end] = {0, root};
            visited_2.set(root);
            while (q_start <= q_end) {
                auto [du, u] = q[q_start++];
                for (auto v : g[u]) {
                    if (visited_2[v]) continue;
                    visited_2.set(v);
                    pair x{du + 1, v};
                    best = max(best, x);
                    q[++q_end] = x;
                }
            }
            ans = max(ans, best.first);
        }
        g.clear_edges();
        for (int j = 0; j < allptr; ++j) {
            int u = all[j];
            used.reset(u);
            visited_1.reset(u);
            visited_2.reset(u);
            g.clear_vertex(u);
        }
        allptr = 0;
    }
    cout << ans + 1 << '\n';
}
