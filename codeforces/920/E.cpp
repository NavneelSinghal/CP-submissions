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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (auto& x : g) sort(begin(x), end(x));

        vector component(n, -1);
        vector<int> component_sz;
        int cur_component = -1;
        vector<int> unvisited(n);
        iota(begin(unvisited), end(unvisited), 0);

        for (int i = 0; i < n; ++i) {
            if (component[i] != -1) continue;
            // i is unvisited, so it must belong to a new component
            queue<int> q;
            cur_component++;
            component_sz.push_back(1);
            component[i] = cur_component;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                int ptr = 0;
                vector<int> remaining_to_visit;
                for (auto v : unvisited) {
                    if (v == u) continue;
                    while (ptr < (int)g[u].size() && g[u][ptr] < v) ++ptr;
                    if (ptr < (int)g[u].size() && v == g[u][ptr]) {
                        // can't visit this now
                        remaining_to_visit.push_back(v);
                    } else {
                        // visit v
                        component[v] = cur_component;
                        ++component_sz.back();
                        q.push(v);
                    }
                }
                unvisited = move(remaining_to_visit);
            }
        }
        sort(begin(component_sz), end(component_sz));
        cout << component_sz.size() << '\n';
        for (auto x : component_sz) cout << x << ' ';
        cout << '\n';
    }
}

