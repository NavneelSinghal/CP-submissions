#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

template <bool multi = true, char A = 'a', int CHARSET = 5>
struct Trie {
    static const int ROOT = 0;
    int sz;
    vector<vector<int>> trie;
    vector<int> freq;

    Trie(int n) {
        sz = 1;
        trie.assign(CHARSET, vector<int>(n + 2, -1));
        freq.assign(n + 2, 0);
    }

    void insert(string& s) {
        int node = ROOT;
        for (auto c : s) {
            int& next_node = trie[c - A][node];
            if (next_node == -1) {
                next_node = sz++;
            }
            node = next_node;
        }
        if constexpr (multi) {
            freq[node]++;
        } else {
            freq[node] = 1;
        }
    }

    int getfreq(string& s) {
        int node = ROOT;
        for (auto c : s) {
            int& next_node = trie[c - A][node];
            if (next_node == -1) {
                return 0;
            }
            node = next_node;
        }
        return freq[node];
    }

    vector<string> listall() {
        vector<string> ans;
        const auto rec = [&](const auto& self, int node, string& s) -> void {
            if (freq[node]) {
                for (int i = 0; i < freq[node]; ++i) ans.push_back(s);
            }
            for (int i = 0; i < CHARSET; ++i) {
                if (trie[i][node] != -1) {
                    s += A + i;
                    self(self, trie[i][node], s);
                    s.pop_back();
                }
            }
        };
        string s = "";
        rec(rec, ROOT, s);
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        int sz = 0;
        for (auto& x : a) cin >> x, sz += x.size();
        Trie<true> freq(sz);
        for (auto& x : a) freq.insert(x);
        for (int i = 0; i < m; ++i) {
            string s;
            cin >> s;
            int sz = 1;
            for (auto x : s)
                if (x == '?') sz *= 6;
            Trie<false> ans(sz * s.size());
            auto solve = [&](const auto& self, int i) -> void {
                if (i == (int)s.size()) {
                    ans.insert(s);
                    return;
                }
                if (s[i] != '?') {
                    // continue
                    self(self, i + 1);
                } else {
                    for (int j = 0; j < 5; ++j) {
                        s[i] = 'a' + j;
                        self(self, i + 1);
                    }
                    // empty
                    s.erase(s.begin() + i);
                    self(self, i);
                    // restore
                    s.insert(s.begin() + i, '?');
                }
            };
            solve(solve, 0);
            int w = 0;
            for (auto& x : ans.listall()) w += freq.getfreq(x);
            cout << w << '\n';
        }
    }
}
