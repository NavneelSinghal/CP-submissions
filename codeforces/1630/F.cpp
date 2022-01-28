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
    std::vector<std::basic_string<int>> g;
    std::vector<int> match_from_left, match_from_right;
    std::vector<int> vis;
    int iteration;

    bipartite_matching(int _n_left, int _n_right)
        : n_left(_n_left),
          n_right(_n_right),
          g(_n_left),
          match_from_left(_n_left, -1),
          match_from_right(_n_right, -1),
          vis(_n_left, 0),
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

constexpr int N = 50005;
std::array<std::basic_string<int>, N> d;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;

    vector<int> id(N, -1);
    for (int i = 1; i < N; ++i)
        for (int j = 2 * i; j < N; j += i) d[j].push_back(i);

    int _tests = 1;
    cin >> _tests;

    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        for (int i = 0; i < n; ++i) id[a[i]] = i;
        bipartite_matching<true> b(2 * n, 2 * n);
        for (int i = 0; i < n; ++i) {
            for (const auto m : d[a[i]]) {
                int j = id[m];
                if (j == -1) continue;
                b.add(i, j);
                b.add(n + i, n + j);
            }
            b.add(i, n + i);
        }
        cout << b.get_max_matching() - n << '\n';
        for (int i = 0; i < n; ++i) id[a[i]] = -1;
    }
}

