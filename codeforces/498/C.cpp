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

struct Random : std::mt19937 {
    using std::mt19937::mt19937;
    using std::mt19937::operator();
    static int64_t gen_seed() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }
    Random() : std::mt19937(gen_seed()) {}
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real> {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};

// consider shuffling adjacency lists if this gives TLE
template <bool ToShuffle = false>
struct bipartite_matching {
    int n_left, n_right;
    std::vector<std::vector<int>> g;
    std::vector<int> match_from_left, match_from_right;
    std::vector<int> vis;
    int iteration;

    bipartite_matching(int _n_left, int _n_right)
        : n_left(_n_left),
          n_right(_n_right),
          g(_n_left),
          vis(_n_left, 0),
          match_from_left(_n_left, -1),
          match_from_right(_n_right, -1),
          iteration(0) {}

    // u on left, v on right
    void add(int u, int v) { g[u].push_back(v); }

    bool dfs(int u) {
        vis[u] = iteration;
        for (auto v : g[u]) {
            if (match_from_right[v] == -1) {
                match_from_right[v] = u;
                match_from_left[u] = v;
                return true;
            }
        }
        for (auto v : g[u]) {
            if (vis[match_from_right[v]] != iteration &&
                dfs(match_from_right[v])) {
                match_from_right[v] = u;
                match_from_left[u] = v;
                return true;
            }
        }
        return false;
    }

    int get_max_matching() {
        if constexpr (ToShuffle) {
            Random rng;
            for (int i = 0; i < n_left; ++i)
                std::random_shuffle(std::begin(g[i]), std::end(g[i]), rng);
        }
        int new_matchings = 0;
        int matchings = 0;
        do {
            iteration++;
            new_matchings = 0;
            for (int u = 0; u < n_left; ++u)
                if (match_from_left[u] == -1 && dfs(u)) new_matchings++;
            matchings += new_matchings;
        } while (new_matchings > 0);
        return matchings;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, m;
        cin >> n >> m;
        vector<int> left, right;
        vector<int> a;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            a.push_back(x);
            if (i & 1)
                left.push_back(x);
            else
                right.push_back(x);
        }
        using pii = pair<int, int>;
        vector<vector<pii>> factor_left, factor_right;
        for (int i = 0; i < n; ++i) {
            vector<pii> fact;
            for (int j = 2; j * j <= a[i]; ++j) {
                if (a[i] % j == 0) {
                    int cnt = 0;
                    while (a[i] % j == 0) a[i] /= j, ++cnt;
                    fact.emplace_back(j, cnt);
                }
            }
            if (a[i] != 1) fact.emplace_back(a[i], 1);
            if (i & 1)
                factor_left.push_back(fact);
            else
                factor_right.push_back(fact);
        }
        int left_i = 0, right_i = 0;
        vector<vector<int>> loc_left, loc_right;
        for (int i = 0; i < n; ++i) {
            if (i & 1) {
                loc_left.emplace_back();
                for (auto [p, pw] : factor_left[i / 2]) {
                    loc_left.back().push_back(left_i);
                    left_i += pw;
                }
            } else {
                loc_right.emplace_back();
                for (auto [p, pw] : factor_right[i / 2]) {
                    loc_right.back().push_back(right_i);
                    right_i += pw;
                }
            }
        }
        bipartite_matching b(left_i, right_i);
        while (m--) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            if (r & 1) swap(l, r);
            l /= 2;
            r /= 2;
            // l in left, r in right
            for (int i = 0; i < (int)loc_left[l].size(); ++i) {
                for (int j = 0; j < (int)loc_right[r].size(); ++j) {
                    if (factor_left[l][i].first == factor_right[r][j].first) {
                        for (int k = loc_left[l][i];
                             k < loc_left[l][i] + factor_left[l][i].second;
                             ++k) {
                            for (int w = loc_right[r][j];
                                 w <
                                 loc_right[r][j] + factor_right[r][j].second;
                                 ++w) {
                                b.add(k, w);
                            }
                        }
                    }
                }
            }
        }
        cout << b.get_max_matching() << '\n';
    }
}

