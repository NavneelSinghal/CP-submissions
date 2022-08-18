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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        int add = 0;
        for (auto x : a)
            if (x > 1) add = 1;

        const int N = 2e5;
        vector<bool> nonempty(N + 1);
        vector<vector<pair<int, int>>> edges(N + 1);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            int g = gcd(a[u], a[v]);
            while (g > 1) {
                int p = sv.spf[g];
                nonempty[p] = true;
                edges[p].emplace_back(u, v);
                while (g % p == 0) g /= p;
            }
        }
        int ans = 0;

        vector<vector<int>> g(n);
        vector<bool> used(n), visited_1(n), visited_2(n);

        for (int i = 2; i <= N; ++i) {
            if (!nonempty[i]) continue;
            auto& edges_p = edges[i];
            vector<int> all;
            for (auto [u, v] : edges_p) {
                g[u].push_back(v);
                g[v].push_back(u);
                if (!used[u]) used[u] = true, all.push_back(u);
                if (!used[v]) used[v] = true, all.push_back(v);
            }
            if (all.empty()) continue;

            for (auto root : all) {
                if (visited_2[root]) continue;
                // now find diameter
                queue<pair<int, int>> q;
                pair<int, int> best{0, root};
                q.emplace(0, root);
                while (not q.empty()) {
                    auto [du, u] = q.front();
                    q.pop();
                    for (auto v : g[u]) {
                        if (visited_1[v]) continue;
                        visited_1[v] = true;
                        pair x{du + 1, v};
                        best = max(best, x);
                        q.push(x);
                    }
                }
                root = best.second;
                best = {0, root};
                q.emplace(0, root);
                visited_2[root] = true;
                while (not q.empty()) {
                    auto [du, u] = q.front();
                    q.pop();
                    for (auto v : g[u]) {
                        if (visited_2[v]) continue;
                        visited_2[v] = true;
                        pair x{du + 1, v};
                        best = max(best, x);
                        q.push(x);
                    }
                }
                ans = max(ans, best.first);
            }

            for (auto u : all) {
                used[u] = false;
                visited_1[u] = false;
                visited_2[u] = false;
                g[u].clear();
            }
        }
        cout << ans + add << '\n';
    }
}

