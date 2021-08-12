#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

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

    vector component(n, -1);
    vector<int> component_sz;
    int cur_component = -1;
    
    vector<int> unvisited_vertices(n);
    iota(begin(unvisited_vertices), end(unvisited_vertices), 0);
    
    vector<int> unvisited_but_unreachable(n);
    queue<int> q;
    
    for (int i = 0; i < n; ++i) {
        if (component[i] != -1) continue;
        cur_component++;
        component_sz.push_back(1);
        component[i] = cur_component;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vector<int> remaining_to_visit;
            for (auto v : g[u])
                if (component[v] == -1)
                    remaining_to_visit.push_back(v),
                        unvisited_but_unreachable[v] = 1;
            for (auto v : unvisited_vertices) {
                if (u == v) continue;
                if (unvisited_but_unreachable[v]) continue;
                component[v] = cur_component;
                ++component_sz.back();
                q.push(v);
            }
            // clear out the buffer
            for (auto v : remaining_to_visit) unvisited_but_unreachable[v] = 0;
            // size of remaining_to_visit is at most deg(u)
            // so complexity remains O(V + E)
            unvisited_vertices = move(remaining_to_visit);
        }
    }

    sort(begin(component_sz), end(component_sz));
    cout << component_sz.size() << '\n';
    for (auto x : component_sz) cout << x << ' ';
    cout << '\n';
}

