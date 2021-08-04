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
        string s;
        cin >> s;
        stringstream st(s);
        string cur;
        vector<int> a;
        while (getline(st, cur, ',')) {
            a.push_back(stoi(cur));
        }
        sort(begin(a), end(a));
        a.erase(unique(begin(a), end(a)), end(a));
        vector<pair<int, int>> range;
        int prv = -1;
        int n = (int)a.size();
        for (int i = 0; i < n; ++i) {
            if (a[i] != prv + 1) {
                range.emplace_back(a[i], a[i]);
            } else {
                range.back().second++;
            }
            prv = a[i];
        }
        int sz = (int)range.size();
        for (int i = 0; i < sz; ++i) {
            auto [l, r] = range[i];
            if (l == r) cout << l;
            else cout << l << '-' << r;
            cout << ",\n"[i == sz - 1];
        }
    }
}
