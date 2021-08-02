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
        int n, m;
        cin >> n >> m;
        const int T = 100;
        vector<int> f(T + 1);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            sum += x;
            int cur = sum;
            int to_remove = 0;
            for (int j = T; j >= 1; --j) {
                if (cur <= m) break;
                int rem = min(f[j], (cur - m + j - 1) / j);
                to_remove += rem;
                cur -= rem * j;
            }
            cout << to_remove << ' ';
            f[x]++;
        }
        cout << '\n';
    }
}
