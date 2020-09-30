#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 5e5 + 5, M = 3e5 + 5, Q = 5e5 + 5;
int n, m, q;
pair<int, int> edge[M], query[Q], t[N * 4];
int a[N], rem[M], par[N], tin[N], tout[N], timer = 0;
vector<int> g[N];

int parent (int x) {
    if (x == par[x]) return x;
    return par[x] = parent(par[x]);
}

void join (int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return;
    ++n;
    par[n] = par[a] = par[b] = n;
    g[n].push_back(a);
    g[n].push_back(b);
}

void dfs (int u) {
    tin[u] = ++timer;
    for (auto v : g[u]) {
        dfs(v);
    }
    tout[u] = timer;
}

pair<int, int> answer (int v, int tl, int tr, int l, int r) {
    if (l > r || tl > r || l > tr) return {0LL, 0LL};
    if (l <= tl && r >= tr) return t[v];
    int tm = (tl + tr) >> 1;
    return max(answer(v << 1, tl, tm, l, r), answer((v << 1) | 1, tm + 1, tr, l, r));
}

void update (int v, int tl, int tr, int i, pair<int, int> x) {
    if (tl == tr) {
        t[v] = x;
        return;
    }
    int tm = (tl + tr) >> 1;
    if (i <= tm) update(v << 1, tl, tm, i, x);
    else update((v << 1) | 1, tm + 1, tr, i, x);
    t[v] = max(t[v << 1], t[(v << 1) | 1]);
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        edge[i] = {u, v};
        rem[i] = 0;
    }
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        query[i] = {a, b};
        if (a == 2) {
            rem[b] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) par[i] = i;
    for (int i = 1; i <= m; ++i) {
        if (!rem[i]) {
            join(edge[i].first, edge[i].second);
        }
    }
    for (int i = q; i; --i) {
        int typ = query[i].first;
        if (typ == 2) {
            int index = query[i].second;
            join(edge[index].first, edge[index].second);
        } else {
            query[i].second = parent(query[i].second);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (parent(i) == i) {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        update(1, 1, n, tin[i], make_pair(a[i], tin[i]));
    }
    for (int i = 1; i <= q; ++i) {
        int typ = query[i].first;
        if (typ == 2) {
            continue;
        }
        int v = query[i].second;
        pair<int, int> temp = answer(1, 1, n, tin[v], tout[v]);
        cout << temp.first << '\n';
        if (temp.first) {
            update(1, 1, n, temp.second, make_pair(0LL, 0LL));
        }
    }
}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
