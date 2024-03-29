#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    using edge = pair<int, int>;
    vector<edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges.emplace_back(u, v);
        edges.emplace_back(v, u);
    }

    auto get_sorted_graph = [](auto& edges, int n) {
        vector<int> cnt(n);
        vector<edge> temp(edges.size());
        for (auto [u, v] : edges) cnt[v]++;
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = (int)edges.size() - 1; i >= 0; --i)
            temp[--cnt[edges[i].second]] = edges[i];
        copy(begin(temp), end(temp), begin(edges));
        fill(begin(cnt), end(cnt), 0);
        for (auto [u, v] : edges) cnt[u]++;
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = (int)edges.size() - 1; i >= 0; --i)
            temp[--cnt[edges[i].first]] = edges[i];
        copy(begin(temp), end(temp), begin(edges));
        vector<vector<int>> g(n);
        for (auto [u, v] : edges) g[u].push_back(v);
        return g;
    };

    auto g = get_sorted_graph(edges, n);
    vector component(n, -1);
    vector<int> component_sz;
    int cur_component = -1;
    vector<int> unvisited(n);
    iota(begin(unvisited), end(unvisited), 0);

    for (int i = 0; i < n; ++i) {
        if (component[i] != -1) continue;
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
                    remaining_to_visit.push_back(v);
                } else {
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
