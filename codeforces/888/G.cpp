#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (name.size() == 0)
        return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    cout << setprecision(10) << fixed;
}

struct binaryTrie {
    // MAX = number of nodes
    static const int CHARSET = 2;
    static const int MAXLEN = 31;
    static const int ROOT = 0;
    
    int sz;
    vector<vector<int>> trie;
    vector<int> cnt;
    vector<int> ends_here;
    vector<int> a;

    // n is the number of total characters, so size needs to be 31 * n
    binaryTrie(int n) {
        sz = 0;
        trie.assign(2, vector<int>(MAXLEN * (n + 2), -1));
        a.resize(n + 1);
        ends_here.resize(MAXLEN * (n + 2));
        cnt.resize(MAXLEN * (n + 2));
    }

    void insert(int n) {
        int node = ROOT;
        int to_insert = a[n];
        for (int i = MAXLEN - 1; ~i; --i) {
            int& next_node = trie[(to_insert >> i) & 1][node];
            if (next_node == -1) {
                next_node = ++sz;
            }
            node = next_node;
            cnt[node]++;
        }
        ends_here[node] = n;
    }

    void remove(int n) { // assumes that n is already inside the trie - if not, then just do a simple traversal
        int node = ROOT;
        int to_remove = a[n];
        for (int i = MAXLEN - 1; ~i; --i) {
            node = trie[(to_remove >> i) & 1][node];
            cnt[node]--;
        }
    }

    pair<int, int> minxor(int n) {
        int node = ROOT;
        int ans = 0;
        int to_use = a[n];
        for (int i = MAXLEN - 1; ~i; --i) {
            ans <<= 1;
            int p = (to_use >> i) & 1;
            int next_node = trie[p][node];
            if (next_node == -1 || cnt[next_node] <= 0) {
                ans ^= 1;
                p ^= 1;
            }
            node = trie[p][node];
        }
        return make_pair(ans, ends_here[node]);
    }

};


vector<int32_t> par, siz;

void make_set(int32_t v) {
    par[v] = v;
    siz[v] = 1;
}

int32_t find_set(int32_t v) {
    if (v == par[v]) return v;
    return par[v] = find_set(par[v]);
}

void union_sets(int32_t a, int32_t b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
    }
}

void solve(int case_no) {

    int n;
    cin >> n;

    par.resize(n + 2);
    siz.resize(n + 2);

    binaryTrie bt(n);

    set<int> unique_elements;

    for (int i = 1; i <= n; ++i) {
        cin >> bt.a[i];
        unique_elements.insert(bt.a[i]);
    }

    n = 0;
    for (auto element : unique_elements) {
        ++n;
        bt.a[n] = element;
        bt.insert(n);
        make_set(n);
    }

    int current_components = n;
    long long ans = 0;

    while (current_components > 1) { // O(log n) iterations

        vector<vector<int>> components(n + 1);
       
        for (int i = 1; i <= n; ++i) {
            components[find_set(i)].push_back(i);
        }

        set<pair<pair<int, int>, int>> chosen_edges;

        for (int i = 1; i <= n; ++i) {
            
            if (!components[i].size()) continue;
            
            for (auto element : components[i]) {
                bt.remove(element);
            }
            
            pair<int, int> shortest_outward = {(int)1e9, (int)1e9};
            
            for (auto element : components[i]) {
                shortest_outward = min(shortest_outward, bt.minxor(element));
            }
    
            int a = i;
            int b = find_set(shortest_outward.second);
            if (a > b) swap(a, b);
            chosen_edges.insert(make_pair(make_pair(a, b), shortest_outward.first));
            
            for (auto element : components[i]) {
                bt.insert(element);
            }
        }

        for (auto edge : chosen_edges) {
            ans += edge.second;
            union_sets(edge.first.first, edge.first.second);
            --current_components;
        }
    }

    cout << ans << endl;

}

signed main() {
    setIO();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        solve(_t);
    }
    return 0;
}
