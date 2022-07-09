#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")

#include "bits/stdc++.h"

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

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

template <int n>
struct st_wrapper {
    template <class Node, class Update, class CombineNodes, class ApplyUpdate,
              class ComposeUpdates = std::nullptr_t,
              class CheckLazy = std::nullptr_t>
    struct lazy_segtree {
        static constexpr bool is_lazy =
            !std::is_same<ComposeUpdates, std::nullptr_t>::value;
        static constexpr bool is_check_lazy =
            !std::is_same<CheckLazy, std::nullptr_t>::value;

        static constexpr int log = [] {
            int x = 0;
            while ((1 << x) < n) ++x;
            return x;
        }();
        static constexpr int size = 1 << log;

       public:
        template <typename... T>
        explicit lazy_segtree(const Node& _id_node,
                              const CombineNodes& _combine,
                              const Update& _id_update,
                              const ApplyUpdate& _apply_update,
                              const ComposeUpdates& _compose_updates = nullptr,
                              const CheckLazy& _check_lazy = nullptr)
            : combine{_combine},
              id_node{_id_node},
              apply_update{_apply_update},
              id_update{_id_update},
              compose_updates{_compose_updates},
              check_lazy{_check_lazy},
              d{},
              lz{} {}

        void set(int p, Node x) {
            p += size;
            if constexpr (is_lazy)
                for (int i = log; i >= 1; i--) push(p >> i);
            d[p] = x;
            for (int i = 1; i <= log; ++i) update(p >> i);
        }

        Node get(int p) {
            p += size;
            if constexpr (is_lazy)
                for (int i = log; i >= 1; i--) push(p >> i);
            return d[p];
        }

        Node query(int l, int r) {
            if (l == r) return id_node;
            l += size, r += size;
            if constexpr (is_lazy) {
                int l_ctz = __builtin_ctz(l);
                int r_ctz = __builtin_ctz(r);
                for (int i = log; i > l_ctz; --i) push(l >> i);
                for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
            }
            Node sml = id_node, smr = id_node;
            while (l < r) {
                if (l & 1) sml = combine(sml, d[l++]);
                if (r & 1) smr = combine(d[--r], smr);
                l >>= 1, r >>= 1;
            }
            return combine(sml, smr);
        }

        Node all_query() const { return d[1]; }

        void update(int p, Update f) {
            p += size;
            if constexpr (is_lazy)
                for (int i = log; i >= 1; i--) push(p >> i);
            d[p] = apply_update(f, d[p]);
            for (int i = 1; i <= log; ++i) update(p >> i);
        }

        void update(int l, int r, Update f) {
            if (l == r) return;
            l += size, r += size;
            const int l_ctz = __builtin_ctz(l);
            const int r_ctz = __builtin_ctz(r);
            if constexpr (is_lazy) {
                for (int i = log; i > l_ctz; --i) push(l >> i);
                for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
            }
            {
                const int l2 = l, r2 = r;
                while (l < r) {
                    if (l & 1) all_apply(l++, f);
                    if (r & 1) all_apply(--r, f);
                    l >>= 1, r >>= 1;
                }
                l = l2, r = r2;
            }
            for (int i = l_ctz + 1; i <= log; ++i) update(l >> i);
            for (int i = r_ctz + 1; i <= log; ++i) update((r - 1) >> i);
        }

        template <class G>
        int max_right(int l, G g) {
            if (l == n) return n;
            l += size;
            if constexpr (is_lazy)
                for (int i = log; i >= 1; i--) push(l >> i);
            Node sm = id_node;
            do {
                while (l % 2 == 0) l >>= 1;
                if (!g(combine(sm, d[l]))) {
                    while (l < size) {
                        if constexpr (is_lazy) push(l);
                        l = (2 * l);
                        if (g(combine(sm, d[l]))) {
                            sm = combine(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = combine(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return n;
        }

        template <class G>
        int min_left(int r, G g) {
            if (r == 0) return 0;
            r += size;
            if constexpr (is_lazy)
                for (int i = log; i >= 1; i--) push((r - 1) >> i);
            Node sm = id_node;
            do {
                r--;
                while (r > 1 && (r % 2)) r >>= 1;
                if (!g(combine(d[r], sm))) {
                    while (r < size) {
                        if constexpr (is_lazy) push(r);
                        r = (2 * r + 1);
                        if (g(combine(d[r], sm))) {
                            sm = combine(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = combine(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

       private:
        CombineNodes combine;
        Node id_node;
        ApplyUpdate apply_update;
        Update id_update;
        ComposeUpdates compose_updates;
        CheckLazy check_lazy;
        Node d[2 * size];
        Update lz[size];

        void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
        void all_apply(int k, Update f) {
            d[k] = apply_update(f, d[k]);
            if constexpr (is_lazy)
                if (k < size) lz[k] = compose_updates(f, lz[k]);
        }
        void push(int k) {
            if constexpr (is_check_lazy)
                if (!check_lazy(lz[k])) return;
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            lz[k] = id_update;
        }
    };
};

using Base = char;
struct Node {
    int c{}, x{};
    ll ans{};
};
constexpr Node id_node{};
constexpr auto combine = [](const Node& l, const Node& r) -> Node {
    return Node{l.c + r.c, l.x + r.x, l.ans + r.ans};
};
using Update = int;
constexpr Update id_update = 0;
constexpr auto apply_update = [](const Update& u, const Node& n) -> Node {
    return Node{n.c + u, n.x, n.ans + ll(n.x) * u};
};
constexpr auto compose_updates = [](const Update& u,
                                    const Update& v) -> Update {
    return u + v;
};
constexpr int N = 200'000;

st_wrapper<N>::lazy_segtree st{id_node, combine, id_update, apply_update,
                               compose_updates};
char x[N];

int main() {
    int q, d;
    cin >> q >> d;
    if (d == 1) {
        while (q--) cout << "0\n";
    } else {
        ll ans = 0;
        while (q--) {
            int i;
            cin >> i;
            --i;
            const int l = max(0, i - d), r = i;
            const auto nd = st.query(l, r), nd2 = st.get(i);
            if (x[i]) {
                x[i] = false;
                ans += -nd.ans + 2 * nd.x - ll(nd2.c - 1) * (nd2.c - 2) / 2;
                st.update(l, r, -1);
                st.set(i, Node{nd2.c - 1, 0, 0});
            } else {
                x[i] = true;
                ans += nd.ans - nd.x + nd2.c * ll(nd2.c - 1) / 2;
                st.update(l, r, 1);
                st.set(i, Node{nd2.c + 1, 1, nd2.c + 1});
            }
            cout << ans << '\n';
        }
    }
}

