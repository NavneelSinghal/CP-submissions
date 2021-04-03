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

namespace treap {

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int INF = 1e9;

struct treap_node {
    int priority, value, cnt;
    bool is_reversed;
    treap_node *left_child, *right_child;
    treap_node(int v)
        : value(v),
          cnt(1),
          left_child(nullptr),
          right_child(nullptr),
          priority(std::uniform_int_distribution<int>(0, INF)(rng)) {}
};

using treap_node_ptr = treap_node *;

int cnt(treap_node_ptr t) { return t ? t->cnt : 0; }

void update_cnt(treap_node_ptr t) {
    if (t) {
        t->cnt = cnt(t->left_child) + cnt(t->right_child) + 1;
    }
}

void push(treap_node_ptr t) {
    if (t && t->is_reversed) {
        t->is_reversed = false;
        std::swap(t->left_child, t->right_child);
        if (t->left_child) t->left_child->is_reversed ^= true;
        if (t->right_child) t->right_child->is_reversed ^= true;
    }
}

void merge(treap_node_ptr &t, treap_node_ptr l, treap_node_ptr r) {
    push(l);
    push(r);
    if (!l || !r) {
        t = (l ? l : r);
    } else if (l->priority > r->priority) {
        merge(l->right_child, l->right_child, r);
        t = l;
    } else {
        merge(r->left_child, l, r->left_child);
        t = r;
    }
    update_cnt(t);
}

void split(treap_node_ptr t, treap_node_ptr &l, treap_node_ptr &r, int key,
           int add = 0) {
    if (!t) {
        l = r = 0;
        return;
    }
    push(t);
    int cur_key = add + cnt(t->left_child);
    if (key <= cur_key) {
        split(t->left_child, l, t->left_child, key, add);
        r = t;
    } else {
        split(t->right_child, t->right_child, r, key,
              add + 1 + cnt(t->left_child));
        l = t;
    }
    update_cnt(t);
}

void insert(treap_node_ptr &t, int pos, int v) {
    treap_node_ptr t1, t2;
    split(t, t1, t2, pos - 1);
    merge(t1, t1, new treap_node(v));
    merge(t, t1, t2);
}

void erase(treap_node_ptr &t, int pos) {
    treap_node_ptr t1, t2, t3;
    split(t, t1, t2, pos - 1);
    split(t2, t2, t3, 1);
    merge(t, t1, t3);
}

void reverse(treap_node_ptr t, int l, int r) {
    treap_node_ptr t1, t2, t3;
    split(t, t1, t2, l - 1);  // one-indexed
    split(t2, t2, t3, r - l + 1);
    t2->is_reversed ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}

void inorder_traversal(treap_node_ptr t, std::vector<int> &a) {
    if (!t) return;
    push(t);
    inorder_traversal(t->left_child, a);
    a.push_back(t->value);
    inorder_traversal(t->right_child, a);
}

void print_treap(treap_node_ptr t) {
    std::vector<int> v;
    inorder_traversal(t, v);
    for (auto x : v) std::cerr << x << ' ';
    std::cerr << '\n';
}

}  // namespace treap

struct curve {
    treap::treap_node_ptr t;
    int last_added;

    curve() : t(nullptr), last_added(0) {}

    void insert_back(int x, bool is_last) {
        if (t == nullptr) {
            t = new treap::treap_node(x);
        } else {
            treap::insert(t, treap::cnt(t) + 1, x);
        }
        if (!is_last) return;
        last_added = treap::cnt(t);
    }

    void insert_front(int x, bool is_last) {
        if (t == nullptr) {
            t = new treap::treap_node(x);
        } else {
            treap::insert(t, 1, x);
        }
        if (!is_last) return;
        last_added = 1;
    }

    void insert_middle(curve &c) {
        if (t == nullptr) {
            t = c.t;
            last_added = c.last_added;
            return;
        }
        treap::treap_node_ptr t1, t2, t3;
        treap::split(t, t1, t2, last_added - 1);
        treap::split(t2, t2, t3, 1);
        treap::merge(t1, t1, c.t);
        treap::merge(t, t1, t3);
        last_added = last_added - 1 + c.last_added;
    }

    void reverse() {
        int cnt_t = treap::cnt(t);
        treap::reverse(t, 1, cnt_t);
        last_added = cnt_t + 1 - last_added;
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin.exceptions(std::cin.failbit | std::cin.badbit);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> cards(2 * n);
    for (auto &[x, y] : cards) std::cin >> x >> y;

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
            std::cout << "NO\n";
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
            std::cout << "NO\n";
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
        curve *ret =
            y_combinator([&](auto solve, int v_start, int v_end) -> curve * {
                if (v_start == v_end) {
                    auto ret = new curve();
                    ret->insert_back(vertices[v_start], 1);
                    return ret;
                }
                char last_orientation = orientations[v_end];
                char first_orientation = orientations[v_start + 1];
                if (last_orientation == first_orientation) {
                    int left_bal = 0;
                    int right_bal = 0;
                    int used = -1;
                    int left_ptr = v_start;
                    int right_ptr = v_end;
                    while (left_ptr < v_end && right_ptr > v_start) {
                        left_bal += 2 * (orientations[left_ptr + 1] == '0') - 1;
                        left_ptr++;
                        if (left_bal == 0) {
                            used = 0;
                            break;
                        }
                        right_bal += 2 * (orientations[right_ptr] == '0') - 1;
                        right_ptr--;
                        if (right_bal == 0) {
                            used = 1;
                            break;
                        }
                    }

                    int mid_ptr = used ? right_ptr : left_ptr;
                    auto left_curve = solve(v_start, mid_ptr);
                    auto right_curve = solve(mid_ptr, v_end);
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
        treap::inorder_traversal(ret->t, indices_order);
        if (cards[indices_order[0]].first < 0)
            std::reverse(std::begin(indices_order), std::end(indices_order));
        for (auto i : indices_order) answer.push_back(i);
    }

    std::cout << "YES\n";
    for (auto i : answer)
        std::cout << cards[i].first << ' ' << cards[i].second << '\n';

    return 0;
}