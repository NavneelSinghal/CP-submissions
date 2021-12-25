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
using ld = long double;

using namespace std;

struct dsu {
    int n;
    vector<int> par;

    // negative - size
    dsu(int n) : n(n), par(n, -1) {}

    int find_set(int v) {
        if (par[v] < 0) return v;
        return par[v] = find_set(par[v]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (par[b] < par[a]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
        return false;
    }

    auto components() {
        vector<int> root(n), size(n);
        for (int i = 0; i < n; ++i) {
            root[i] = find_set(i);
            size[root[i]]++;
        }
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; ++i) ans[i].reserve(size[i]);
        for (int i = 0; i < n; ++i) ans[root[i]].push_back(i);
        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const auto& v) { return v.empty(); }),
                  ans.end());
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";

        int n;
        cin >> n;

        vector<int> p(n);
        for (auto& x : p) cin >> x, --x;

        int m;
        cin >> m;

        vector<vector<int>> g(n);
        map<pair<int, int>, int> mp;

        vector<int> moves;

        dsu dsu(n);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
            mp[{u, v}] = i;
            mp[{v, u}] = i;
            dsu.union_sets(u, v);
        }

        bool works = true;

        auto components = dsu.components();

        for (auto& component : components) {
            vector<int> v;
            sort(begin(component), end(component));
            for (auto i : component) v.push_back(p[i]);
            sort(begin(v), end(v));
            if (v != component) {
                works = false;
                break;
            }
            int iter = (int)v.size();
            vector<int> dead(n);

            // find non-articulation point at each step
            for (int i = 0; i < iter; ++i) {
                // find articulation points
                vector<bool> visited(n, false);
                vector<int> tin(n, -1), low(n, -1);
                int timer = 0;
                vector<bool> is_cutpoint(n, false);
                auto dfs = [&](const auto& self, int v, int p = -1) -> void {
                    visited[v] = true;
                    tin[v] = low[v] = timer++;
                    int children = 0;
                    for (int to : g[v]) {
                        if (to == p) continue;
                        if (visited[to]) {
                            low[v] = min(low[v], tin[to]);
                        } else {
                            self(self, to, v);
                            low[v] = min(low[v], low[to]);
                            if (low[to] >= tin[v] && p != -1)
                                is_cutpoint[v] = true;
                            ++children;
                        }
                    }
                    if (p == -1 && children > 1) is_cutpoint[v] = true;
                };

                int start = -1;
                for (int i = 0; i < iter; ++i)
                    if (!dead[v[i]]) start = v[i];

                dfs(dfs, start, -1);

                // choose something that is not dead and not an articulation
                // point either
                int chosen = -1;
                for (auto u : v) {
                    if (!dead[u] && !is_cutpoint[u]) {
                        chosen = u;
                        break;
                    }
                }
                assert(chosen != -1);

                if (p[chosen] != chosen) {
                    int s = chosen;
                    int stop = -1;

                    queue<int> q;
                    vector<bool> used(n);
                    vector<int> par(n);

                    q.push(s);
                    used[s] = true;
                    par[s] = -1;
                    while (!q.empty()) {
                        int v = q.front();
                        if (p[v] == s) {
                            stop = v;
                            break;
                        }
                        q.pop();
                        for (int u : g[v]) {
                            if (!used[u]) {
                                used[u] = true;
                                q.push(u);
                                par[u] = v;
                            }
                        }
                    }
                    vector<int> path;
                    while (stop != -1) {
                        path.push_back(stop);
                        stop = par[stop];
                    }
                    for (int i = 0; i + 1 < (int)path.size(); ++i) {
                        moves.push_back(mp[{path[i], path[i + 1]}] + 1);
                        swap(p[path[i]], p[path[i + 1]]);
                    }
                }

                // remove this vertex from the graph
                dead[chosen] = true;
                for (auto i : v) {
                    auto it = find(begin(g[i]), end(g[i]), chosen);
                    if (it != g[i].end()) g[i].erase(it);
                }
                g[chosen].clear();
            }
        }

        if (!works) {
            cout << -1 << '\n';
        } else {
            // assert(moves.size() <= 500000);
            assert(is_sorted(begin(p), end(p)));
            cout << moves.size() << '\n';
            for (auto i : moves) cout << i << ' ';
            cout << '\n';
        }
    }
}
