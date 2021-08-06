#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, e;
        cin >> n >> e;
        vector<vector<int>> g(n);
        for (int i = 0; i < e; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> conference(n, -1);
        for (int i = 0; i < n; ++i) {
            int cnt[2]{0, 0};
            for (auto u : g[i])
                if (conference[u] != -1) cnt[conference[u]]++;
            if (cnt[1] >= cnt[0])
                conference[i] = 0;
            else
                conference[i] = 1;
        }
        vector<vector<int>> wish(n);
        vector<int> cnt(1'000'000);
        int T = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            while (x--) {
                int u;
                cin >> u;
                wish[i].push_back(u - 1);
                cnt[u - 1]++;
                T = max(T, u);
            }
        }
        vector<int> good_teams;
        for (int i = 0; i < T; ++i)
            if (cnt[i]) good_teams.push_back(i);
        Random rng;
        while (true) {
            random_shuffle(begin(good_teams), end(good_teams), rng);
            vector<int> location(T);
            for (auto x : good_teams) location[x] = rng(0, 1);
            vector<int> assignment(n, -1);
            bool found = true;
            for (int i = 0; i < n; ++i) {
                for (auto team : wish[i]) {
                    if (location[team] == conference[i]) {
                        assignment[i] = team;
                        break;
                    }
                }
                if (assignment[i] == -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                for (int i = 0; i < n; ++i)
                    cout << assignment[i] + 1 << " \n"[i == n - 1];
                vector<int> teamconf(T);
                for (int i = 0; i < n; ++i) teamconf[assignment[i]] = conference[i];
                for (int i = 0; i < T; ++i)
                    cout << teamconf[i] + 1 << " \n"[i == T - 1];
                return 0;
            }
        }
    }
}

