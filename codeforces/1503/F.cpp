#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

const int N = 130;

static char buf[N << 20];
void *operator new(size_t s) {
    static size_t i = sizeof buf;
    return (void *)&buf[i -= s];
}
void operator delete(void *) {}

template <class Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}
    template <class... Args>
    decltype(auto) operator()(Args &&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

namespace IO {
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

inline void read_char(char &c) {
    while (isspace(next_char(false))) next_char();

    c = next_char();
}

template <typename T>
inline void read_int(T &number) {
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
inline void read_int(T &number, Args &... args) {
    read_int(number);
    read_int(args...);
}

inline void read_str(std::string &str) {
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

inline void write_str(const std::string &str, char after = '\0') {
    for (char c : str) write_char(c);

    if (after) write_char(after);
}

void IOinit() {
    // Make sure _flush_output() is called at the end of the program.
    bool exit_success = atexit(_flush_output) == 0;
    assert(exit_success);

    for (int i = 0; i < 100; i++) lookup[i] = uint8_t((i / 10 << 4) + i % 10);
}
}  // namespace IO

struct curve {
    std::list<int> a, b;
    std::list<int>::iterator last_added_a, last_added_b;

    curve() : a(), b(), last_added_a(std::end(a)), last_added_b(std::end(b)) {}

    void insert_back(int x, bool is_last) {
        a.push_back(x);
        b.push_front(x);
        if (!is_last) return;
        last_added_a = std::prev(a.end());
        last_added_b = b.begin();
    }

    void insert_front(int x, bool is_last) {
        a.push_front(x);
        b.push_back(x);
        if (!is_last) return;
        last_added_a = a.begin();
        last_added_b = std::prev(b.end());
    }

    void insert_middle(curve &c) {
        a.splice(last_added_a, c.a);
        a.erase(last_added_a);
        b.splice(last_added_b, c.b);
        b.erase(last_added_b);
        std::swap(last_added_a, c.last_added_a);
        std::swap(last_added_b, c.last_added_b);
        c.a.clear();
        c.b.clear();
    }

    void reverse() {
        a.swap(b);
        std::swap(last_added_a, last_added_b);
    }
};

int main() {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0);
    // std::cin.exceptions(std::cin.failbit | std::cin.badbit);
    
    IO::IOinit();

    int n;
    IO::read_int(n);
    // std::cin >> n;
    std::vector<std::pair<int, int>> cards(2 * n);
    for (auto &[x, y] : cards) IO::read_int(x, y); // std::cin >> x >> y;

    auto normalize_value = [&](int x) {
        if (x < 0)
            return x + n;
        else
            return x + n - 1;
    };

    // find matching pairs
    std::vector<int> front_match(2 * n), back_match(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        front_match[normalize_value(cards[i].first)] = i;
        back_match[normalize_value(cards[i].second)] = i;
    }

    const int FRONT = 0;
    const int BACK = 1;

    // g[u] stores (v, side) where side is the side used for the edge
    std::vector<std::vector<std::pair<int, int>>> g(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        int current_bracket, matching_bracket;
        current_bracket = front_match[normalize_value(cards[i].first)];
        matching_bracket = front_match[normalize_value(-cards[i].first)];
        g[current_bracket].emplace_back(matching_bracket, FRONT);
        current_bracket = back_match[normalize_value(cards[i].second)];
        matching_bracket = back_match[normalize_value(-cards[i].second)];
        g[current_bracket].emplace_back(matching_bracket, BACK);
    }

    // now decompose g into cycles and solve for each cycle separately
    std::vector<char> visited(2 * n);
    std::vector<int> parent(2 * n);
    std::vector<int> answer;
    answer.reserve(2 * n);

    for (int vertex = 0; vertex < 2 * n; ++vertex) {
        if (visited[vertex]) continue;

        int cycle_start = -1, cycle_end = -1;
        int last_incoming_side = -1;
        y_combinator([&](const auto dfs, int u, int p, int side_u) -> bool {
            visited[u] = 1;
            for (auto &[v, side_v] : g[u]) {
                if (v == p && side_v == side_u) continue;
                if (!visited[v]) {
                    parent[v] = u;
                    if (dfs(v, u, side_v)) return true;
                } else {
                    cycle_start = v;
                    cycle_end = u;
                    last_incoming_side = side_u;
                    return true;
                }
            }
            return false;
        })(vertex, -1, 0);

        std::vector<int> cycle;

        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.emplace_back(v);
        cycle.emplace_back(cycle_start);

        if (cycle.size() % 2 == 1) {
            // std::cout << "NO\n";
            IO::write_str("NO\n");
            return 0;
        }

        using edge = std::array<int, 3>;

        // look for orientations of edges
        int cycle_size = (int)cycle.size();
        int current_side = last_incoming_side;
        std::vector<edge> edges;

        for (int i = 0; i < cycle_size; ++i) {
            int current_index = cycle[i];
            int next_index = cycle[(i + 1) % cycle_size];
            auto it = std::find(std::begin(g[current_index]),
                                std::end(g[current_index]),
                                std::make_pair(next_index, current_side));
            int orientation = current_side;
            if (current_side == FRONT)
                orientation ^= cards[current_index].first < 0;
            else
                orientation ^= cards[current_index].second < 0;
            edges.emplace_back(edge{current_index, next_index, orientation});
            current_side ^= 1;
        }

        int cnt0 = 0, cnt1 = 0;
        for (auto &[x, y, z] : edges) {
            if (z == 0)
                cnt0++;
            else
                cnt1++;
        }

        if (abs(cnt1 - cnt0) != 2) {
            IO::write_str("NO\n");
            // std::cout << "NO\n";
            return 0;
        }

        if (cnt0 > cnt1) {
            std::swap(cnt0, cnt1);
            for (auto &[x, y, z] : edges) z ^= 1;
        }

        int loc = -1;
        for (int i = 1; i < (int)edges.size(); ++i)
            if (edges[i][2] == edges[i - 1][2] && edges[i][2] == 1) {
                loc = i;
                break;
            }

        std::rotate(std::begin(edges), std::begin(edges) + loc,
                    std::end(edges));

        if (cards[edges[0][0]].first < 0) {
            std::reverse(std::begin(edges), std::end(edges));
            for (auto &[x, y, z] : edges) std::swap(x, y);
        }

        std::vector<int> vertices;
        vertices.reserve((int)edges.size() - 1);
        for (int i = 0; i + 1 < (int)edges.size(); ++i)
            vertices.push_back(edges[i][1]);
        std::string orientations;
        for (auto &[x, y, z] : edges) orientations += '0' + (char)z;
        std::vector<int> matching_location(edges.size(), -1);

        std::stack<int> matching_stack;
        for (int i = 1; i + 1 < (int)orientations.size(); ++i) {
            if (matching_stack.empty()) {
                matching_stack.push(i);
            } else {
                if (orientations[matching_stack.top()] == orientations[i]) {
                    matching_stack.push(i);
                } else {
                    int other = matching_stack.top();
                    matching_stack.pop();
                    matching_location[i] = other;
                    matching_location[other] = i;
                }
            }
        }

        curve *ret =
            y_combinator([&](auto solve, int v_start, int v_end) -> curve * {
                if (v_start == v_end) {
                    auto ret = new curve();
                    ret->insert_back(vertices[v_start], 1);
                    return ret;
                }
                char last_orientation = orientations[v_end];
                char first_orientation = orientations[v_start + 1];
                if (last_orientation == first_orientation ||
                    (matching_location[v_start + 1] != v_end)) {
                    int first_match_end = matching_location[v_start + 1];
                    auto left_curve = solve(v_start, first_match_end);
                    auto right_curve = solve(first_match_end, v_end);
                    left_curve->insert_middle(*right_curve);
                    return left_curve;
                } else {
                    auto x = vertices[v_start];
                    auto y = vertices[v_end];
                    auto ret = solve(v_start + 1, v_end - 1);
                    ret->reverse();
                    if (last_orientation == '1') {
                        ret->insert_front(x, 0);
                        ret->insert_back(y, 1);
                    } else {
                        ret->insert_front(y, 1);
                        ret->insert_back(x, 0);
                    }
                    return ret;
                }
            })(0, (int)vertices.size() - 1);

        std::vector<int> indices_order{edges[0][0]};
        std::vector<int> alternative_order;
        for (auto x : ret->a) indices_order.push_back(x);
        if (cards[indices_order[0]].first < 0)
            std::reverse(std::begin(indices_order), std::end(indices_order));
        for (auto i : indices_order) answer.push_back(i);
    }

    // std::cout << "YES\n";
    IO::write_str("YES\n");
    for (auto i : answer) {
        IO::write_int(cards[i].first, ' ');
        IO::write_int(cards[i].second, '\n');
        // std::cout << cards[i].first << ' ' << cards[i].second << '\n';
    }

    return 0;
}