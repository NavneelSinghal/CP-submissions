#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> g1(n), g2(n);
        for (int i = 1; i < n; ++i) {
            int x;
            cin >> x;
            --x;
            g1[x].push_back(i);
        }
        for (int i = 1; i < n; ++i) {
            int x;
            cin >> x;
            --x;
            g2[x].push_back(i);
        }
        vector<int> in_time(n), out_time(n);
        int timer = 0;
        auto compute_time = [&](const auto &self, int u) -> void {
            in_time[u] = timer++;
            for (auto v : g2[u]) self(self, v);
            out_time[u] = timer++;
        };
        compute_time(compute_time, 0);
        auto is_anc = [&](int u, int v) {
            return in_time[u] <= in_time[v] && out_time[v] <= out_time[u];
        };
        int ans = 1;
        int cur = 1;
        set<pair<int, int>> s;
        auto dfs = [&](const auto &self, int u) -> void {
            int old = cur;
            auto it = s.lower_bound(pair{in_time[u], 0});
            if (it != s.end()) cur += !is_anc(u, it->second);
            if (it != s.begin()) {
                auto it2 = it;
                --it;
                cur += !is_anc(it->second, u);
                if (it2 != s.end())
                    cur -= !is_anc(it->second, it2->second);
            }
            ans = max(ans, cur);
            s.emplace(in_time[u], u);
            for (auto v : g1[u]) self(self, v);
            s.erase({in_time[u], u});
            cur = old;
        };
        dfs(dfs, 0);
        cout << ans << '\n';
    }
    return 0;
}
