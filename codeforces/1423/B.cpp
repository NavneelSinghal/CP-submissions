#pragma GCC optimize ("Ofast")
//#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 20001
#define NIL 0
#define INF (1<<28)

vector<int> G[MAX];

int n, m, match[MAX], dist[MAX];

// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in G
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int32_t main() {

    fastio;

    cin >> n;
    m = n;
    int M;
    cin >> M;
    vector<pair<pair<int, int>, int>> edges;
    
    while (M--) {
        int u, v, d;
        cin >> u >> v >> d;
        edges.emplace_back(make_pair(u, v), d);
    }

    int l = 0;
    int r = 2e9;
    int ans = 2e9;

    while (l <= r) {
        int m = (l + r) >> 1;
        for (int i = 0; i < MAX; ++i) G[i].clear(), match[i] = 0, dist[i] = 0;
        for (auto p : edges) {
            if (p.second <= m) {
                int u = p.first.first;
                int v = n + p.first.second;
                G[u].push_back(v);
                G[v].push_back(u);
            }
        }
        int matching = hopcroft_karp();
        if (matching == n) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    if (ans == 2e9) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
