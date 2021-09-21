#include "bits/stdc++.h"
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    for (auto& x : a) {
        int s;
        cin >> s;
        x.resize(s);
        for (auto& y : x) cin >> y;
        reverse(begin(x), end(x));
    }
    int m;
    cin >> m;
    using A = array<int, 10>;
    map<A, int> mp;
    A b{};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) cin >> b[j], b[j] = a[j].size() - b[j];
        mp[b] = true;
    }
    priority_queue<pair<int, A>, vector<pair<int, A>>, greater<pair<int, A>>>
        pq;
    map<A, int> d;
    pq.emplace(0, A{});
    while (!pq.empty()) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (!mp[v]) {
            for (int i = 0; i < n; ++i) cout << a[i].size() - v[i] << ' ';
            cout << '\n';
            return 0;
        }
        for (int i = 0; i < n; ++i) {
            if (v[i] != (int)a[i].size() - 1) {
                auto vv = v;
                vv[i]++;
                if (d.find(vv) == d.end())
                    pq.emplace(dv + a[i][v[i]] - a[i][vv[i]], vv),
                        d[vv] = dv + a[i][v[i]] - a[i][vv[i]];
            }
        }
    }
}