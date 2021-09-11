#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,bmi,bmi2")
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

template <class T, class U = T>
bool ckmin(T& a, U&& b) {
    return b < a ? a = std::forward<U>(b), true : false;
}

struct binaryTrie {
    static constexpr int MAXLEN = 20;
    static constexpr int ROOT = 0;
    static constexpr int MX = 1e9;

    struct Node {
        array<int, 2> ch;
        int mn;
    };

    int sz;
    vector<Node> trie;

    binaryTrie() {
        sz = 0;
        trie.assign(1, Node{array{-1, -1}, MX});
    }

    void insert(int n) {
        int node = ROOT;
        for (int i = MAXLEN - 1; ~i; --i) {
            int p = (n >> i) & 1;
            if (trie[node].ch[p] == -1) {
                trie.emplace_back(Node{array{-1, -1}, n});
                trie[node].ch[p] = ++sz;
            }
            node = trie[node].ch[p];
            ckmin(trie[node].mn, n);
        }
    }

    int answer(int xorwith, int bound) {
        int node = ROOT;
        int ans = 0;
        for (int i = MAXLEN - 1; ~i; --i) {
            ans <<= 1;
            int p = !((xorwith >> i) & 1);
            auto& nd = trie[node];
            if (nd.ch[p] != -1 && trie[nd.ch[p]].mn <= bound)
                ;
            else if (nd.ch[p ^ 1] != -1 && trie[nd.ch[p ^ 1]].mn <= bound)
                p ^= 1;
            else
                return -1;
            ans ^= p;
            node = nd.ch[p];
        }
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
        const int N = (int)1e5 + 5;
        vector<vector<int>> divs(N);
        for (int i = 1; i < N; ++i)
            for (int j = i; j < N; j += i) divs[j].push_back(i);
        set<int> s;
        vector<binaryTrie> trie(N);
        int q;
        cin >> q;
        while (q--) {
            int t;
            cin >> t;
            if (t == 1) {
                int u;
                cin >> u;
                if (s.find(u) == s.end()) {
                    s.insert(u);
                    debug(divs[u]);
                    for (auto d : divs[u]) trie[d].insert(u);
                }
            } else {
                int x, k, b;
                cin >> x >> k >> b;
                if (x % k != 0)
                    cout << -1 << '\n';
                else if (b < x)
                    cout << -1 << '\n';
                else
                    cout << trie[k].answer(x, b - x) << '\n';
            }
        }
    }
}
