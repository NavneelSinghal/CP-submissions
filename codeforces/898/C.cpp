#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

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
    for (int test = 1; test <= t; ++test) {
        map<string, set<string>> m;
        int n;
        cin >> n;
        while (n--) {
            string s;
            cin >> s;
            int nums;
            cin >> nums;
            while (nums--) {
                string w;
                cin >> w;
                m[s].insert(w);
            }
        }
        cout << m.size() << '\n';
        for (auto& [x, y] : m) {
            auto w = y;
            for (auto& z : w) {
                bool to_remove = false;
                for (auto& e : y) {
                    if (z.size() < e.size() && e.substr(e.size() - z.size()) == z) {
                        to_remove = true;
                        break;
                    }
                }
                if (to_remove) y.erase(z);
            }
            cout << x << ' ' << y.size() << ' ';
            for (auto s : y) cout << s << ' ';
            cout << '\n';
        }
    }
}
