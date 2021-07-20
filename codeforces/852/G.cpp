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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for (auto& x : a) cin >> x;
        map<string, int> freq;
        for (auto& x : a) freq[x]++;
        for (int i = 0; i < m; ++i) {
            string s;
            cin >> s;
            set<string> ans;
            auto solve = [&](const auto& self, int i) -> void {
                if (i == (int)s.size()) {
                    ans.insert(s);
                    return;
                }
                if (s[i] != '?') {
                    // continue
                    self(self, i + 1);
                } else {
                    for (int j = 0; j < 6; ++j) {
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
            for (auto& x : ans) w += freq[x];
            cout << w << '\n';
        }
    }
}
