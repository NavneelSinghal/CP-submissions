#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;
using ll = long long;

struct Dinic {
    vector<int> lvl, ptr, q;
    using A = array<ll, 4>;
    vector<vector<A>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void add_edge(int a, int b, int c, int rcap = 0) {
        adj[a].push_back(A{b, (int)adj[b].size(), c, 0});
        adj[b].push_back(A{a, (int)adj[a].size() - 1, rcap, 0});
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int i = ptr[v]; i < (int)adj[v].size(); ++i) {
            auto e = adj[v][i];
            if (lvl[e[0]] == lvl[v] + 1) {
                auto p = dfs(e[0], t, min(f, e[2] - e[3]));
                if (p) {
                    adj[v][i][3] += p;
                    adj[e[0]][e[1]][3] -= p;
                    return p;
                }
            }
            ++ptr[v];
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0;
        q[0] = s;
        for (int l = 0; l < 31; ++l) {
            for (;;) {
                fill(begin(lvl), end(lvl), 0);
                fill(begin(ptr), end(ptr), 0);
                int qi = 0, qe = 1;
                lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    auto v = q[qi];
                    ++qi;
                    for (auto e : adj[v]) {
                        if (!lvl[e[0]] && (uint64_t(e[2] - e[3]) >> (30 - l))) {
                            q[qe] = e[0];
                            ++qe;
                            lvl[e[0]] = lvl[v] + 1;
                        }
                    }
                }
                auto p = dfs(s, t, 1e9);
                while (p) {
                    flow += p;
                    p = dfs(s, t, 1e9);
                }
                if (!lvl[t]) break;
            }
        }
        return flow;
    }
};

struct dsu {
    int n;
    vector<int> par;

    // negative - size
    dsu(int n) : n(n), par(n, -1) {}

    int root(int v) {
        if (par[v] < 0) return v;
        return par[v] = root(par[v]);
    }

    bool join(int a, int b) {
        a = root(a);
        b = root(b);
        if (a != b) {
            if (par[b] < par[a]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
        return false;
    }

    int size(int a) {
        a = root(a);
        return -par[a];
    }

    auto components() {
        vector<int> roots(n), size(n);
        for (int i = 0; i < n; ++i) {
            roots[i] = root(i);
            size[roots[i]]++;
        }
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; ++i) ans[i].reserve(size[i]);
        for (int i = 0; i < n; ++i) ans[roots[i]].push_back(i);
        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const auto& v) { return v.empty(); }),
                  ans.end());
        return ans;
    }

    int count_components() {
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (root(i) == i) ans++;
        return ans;
    }
};

int main() {
    // cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        vector<bitset<501>> L(m);
        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;
            for (int i = 0; i < m; ++i) L[i][j] = s[i] - '0';
        }

        Dinic mf(2 * m + 2);
        auto so = 2 * m;
        auto si = so + 1;
        for (int i = 0; i < m; ++i) {
            mf.add_edge(so, i, 1);
            mf.add_edge(i + m, si, 1);
            for (int j = 0; j < m; ++j) {
                if (i == j) continue;
                auto& s = L[i];
                auto& t = L[j];
                bool good = true;
                for (int k = 0; k < n; ++k) good = good && (s[k] >= t[k]);
                if (s == t && i > j) continue;
                if (good) mf.add_edge(i, j + m, 1);
            }
        }
        cout << m - mf.calc(so, si) << '\n';
        dsu uf(m);
        for (int i = 0; i < m; ++i) {
            auto& uu = mf.adj[i];
            assert(uu[0][0] == so);
            if (uu[0][3] == -1) {
                for (int pos = 1; pos < (int)uu.size(); ++pos) {
                    auto l = uu[pos];
                    if (l[3] == 1) {
                        uf.join(i, l[0] - m);
                    }
                }
            }
        }
        vector<int> gr;
        for (int i = 0; i < m; ++i) gr.push_back(uf.root(i));
        auto ind = 1;
        map<int, int> mm;
        vector<int> tgr;
        for (int i = 0; i < m; ++i) {
            if (!mm.count(gr[i])) {
                mm[gr[i]] = ind;
                ++ind;
            }
            tgr.push_back(mm[gr[i]]);
        }
        vector<int> wa;
        for (auto& uu : L) wa.push_back(n + 2 - uu.count());
        for (auto x : tgr) cout << x << ' ';
        cout << '\n';
        for (auto x : wa) cout << x << ' ';
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            vector<int> need(ind, 1);
            for (int j = 0; j < m; ++j) {
                if (L[j][i]) {
                    need[tgr[j]] = max(need[tgr[j]], wa[j]);
                }
            }
            for (int i = 1; i < (int)need.size(); ++i) cout << need[i] << ' ';
            cout << '\n';
        }
    }
}
