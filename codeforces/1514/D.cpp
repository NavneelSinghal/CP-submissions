#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

namespace IO {
#define CUSTOM_IO
    using namespace std;
    const int BUFFER_SIZE = 1 << 15;
    char input_buffer[BUFFER_SIZE];
    size_t input_pos = 0, input_len = 0;
    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
    char number_buffer[100];
    uint8_t lookup[100];
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) input_buffer[0] = EOF;
    }
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();
        return input_buffer[advance ? input_pos++ : input_pos];
    }
    inline bool isspace(char c) {
        return (unsigned char)(c - '\t') < 5 || c == ' ';
    }
    inline void read_char(char& c) {
        while (isspace(next_char(false))) next_char();
        c = next_char();
    }
    template <typename T>
    inline void read_int(T& number) {
        bool negative = false;
        number = 0;
        while (!isdigit(next_char(false)))
            if (next_char() == '-') negative = true;
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
        if (negative) number = -number;
    }
    template <typename T, typename... Args>
    inline void read_int(T& number, Args&... args) {
        read_int(number);
        read_int(args...);
    }
    inline void read_str(string& str) {
        while (isspace(next_char(false))) next_char();
        str.clear();
        do {
            str += next_char();
        } while (!isspace(next_char(false)));
    }
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();
        output_buffer[output_pos++] = c;
    }
    template <typename T>
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
    inline void write_str(const string& str, char after = '\0') {
        for (char c : str) write_char(c);
        if (after) write_char(after);
    }
    void IOinit() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
        for (int i = 0; i < 100; i++)
            lookup[i] = uint8_t((i / 10 << 4) + i % 10);
    }
}  // namespace IO

using namespace std;

// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
struct lazy_segtree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;

   public:
    template <typename... T>
    explicit lazy_segtree(int n, const Base& id_base, T... args)
        : lazy_segtree(std::vector<Base>(n, id_base), args...) {}
    explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr)
        : _n(int(v.size())),
          make_node(_make_node),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<Node>(2 * size, id_node);
        if constexpr (is_lazy) lz = std::vector<Update>(size, id_update);
        for (int i = 0; i < _n; i++) d[size + i] = make_node(v[i], i);
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
    
    void set(int p, Node x) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
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
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }
        Node sml = id_node, smr = id_node;
        while (l < r) {
            if (l & 1) sml = combine(sml, d[l++]);
            if (r & 1) smr = combine(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return combine(sml, smr);
    }
    Node all_query() { return d[1]; }
    void update(int p, Update f) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply_update(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void update(int l, int r, Update f) {
        if (l == r) return;
        l += size, r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(Node)>
    int max_right(int l) {
        return max_right(l, [](Node x) { return g(x); });
    }
    template <class G>
    int max_right(int l, G g) {
        // assert(0 <= l && l <= _n);
        // assert(g(id_node));
        if (l == _n) return _n;
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
        return _n;
    }

    template <bool (*g)(Node)>
    int min_left(int r) {
        return min_left(r, [](Node x) { return g(x); });
    }
    template <class G>
    int min_left(int r, G g) {
        // assert(0 <= r && r <= _n);
        // assert(g(id_node));
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
    int _n, size, log;
    std::vector<Node> d;
    std::vector<Update> lz;
    const MakeNode make_node;
    const CombineNodes combine;
    const Node id_node;
    const ApplyUpdate apply_update;
    const Update id_update;
    const ComposeUpdates compose_updates;

    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        if constexpr (is_lazy) lz[k] = id_update;
    }
};

/* verification: judge.yosupo.jp (both lazy and non-lazy)
 *
 * usage example:
    struct Node { mint sum, size; };
    const Node id_node = {0, 0};
    using Base = mint;
    auto make_node = [](const Base& c, int i) {
        return Node{c, 1};
    };
    auto combine = [](const Node& n1, const Node& n2) {
        return Node{n1.sum + n2.sum, n1.size + n2.size};
    };
    struct Update { mint a, b; };
    const Update id_update = {1, 0};
    auto apply_update = [](const Update& u, const Node& nd) {
        return Node{nd.sum * u.a + nd.size * u.b, nd.size};
    };
    auto compose_updates = [](const Update& u, const Update& v) {
        return Update{u.a * v.a, u.a * v.b + u.b};
    };
    vector<Base> a(n);
    for (auto& x : a) IO::read_int(x.v_);
    lazy_segtree seg(a, id_node, make_node, combine, id_update, apply_update,
                     compose_updates);
    static_assert(decltype(seg)::is_lazy);
*/

// clang-format on

int main() {
    IO::IOinit();

    int n, q;
    IO::read_int(n, q);

    vector<int> a(n);
    for (auto& x : a) IO::read_int(x);

    vector<vector<int>> loc(n + 1);
    for (int i = 0; i < n; ++i) loc[a[i]].push_back(i);

    auto get_freq = [&](int x, int l, int r) {
        return lower_bound(begin(loc[x]), end(loc[x]), r) -
               lower_bound(begin(loc[x]), end(loc[x]), l);
    };

    struct Node {
        int val, freq, l, r;
    };
    const Node id_node = {0, 0, -1, -1};
    using Base = int;
    auto make_node = [](const Base& c, int i) {
        return Node{c, 1, i, i + 1};
    };
    auto combine = [&](const Node& n1, const Node& n2) {
        if (n1.l == -1) return n2;
        if (n2.l == -1) return n1;
        if (n1.val == n2.val)
            return Node{n1.val, n1.freq + n2.freq, n1.l, n2.r};
        auto freq_1 = get_freq(n1.val, n1.l, n2.r);
        auto freq_2 = get_freq(n2.val, n1.l, n2.r);
        if (freq_1 > freq_2) {
            return Node{n1.val, freq_1, n1.l, n2.r};
        } else {
            return Node{n2.val, freq_2, n1.l, n2.r};
        }
    };
    struct Update {};
    const Update id_update = {};
    auto apply_update = [](const Update& u, const Node& nd) {
        return nd;
    };
    auto compose_updates = [](const Update& u, const Update& v) {
        return u;
    };
    lazy_segtree seg(a, id_node, make_node, combine, id_update, apply_update);
    static_assert(!decltype(seg)::is_lazy);

    for (int i = 0; i < q; ++i) {
        int l, r;
        IO::read_int(l, r);
        --l;
        Node nd = seg.query(l, r);
        int len = r - l;
        if (nd.freq <= (len + 1) / 2) {
            IO::write_int(1, '\n');
        } else {
            IO::write_int(2 * nd.freq - len, '\n');
        }
    }
}
