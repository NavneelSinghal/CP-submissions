#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> sum(n + 1), parity(n + 1, -1);
        for (int i = 0, par = 1; i < n; ++i, par *= -1) {
            parity[i + 1] = par * (int(s[i] == '+') - int(s[i] == '-'));
            sum[i + 1] = sum[i] + parity[i + 1];
        }
        vector loc(2, vector<vector<int>>(2 * n + 2));
        const int offset = n;
        for (int i = 0; i <= n; ++i)
            loc[(parity[i] + 1) / 2][offset + sum[i]].push_back(i);
        while (q--) {
            int l, r;
            cin >> l >> r;
            --l;
            if (sum[r] - sum[l] == 0) {
                cout << 0 << '\n';
                continue;
            }
            if ((sum[r] - sum[l]) & 1) {
                cout << 1 << '\n';
            } else {
                cout << 2 << '\n';
                cout << r << ' ';
                --r;
            }
            bool found = false;
            int k = -1;
            // [l + 1, r + 1) - find element k such that pre[k] = (parity[k]
            // + pre[l] + pre[r]) / 2
            for (int p = -1; p < 2; p += 2) {
                int idx = (p + 1) / 2;
                int search = (p + sum[l] + sum[r]) / 2;
                auto it = lower_bound(begin(loc[idx][search + offset]),
                                      end(loc[idx][search + offset]), l + 1);
                if (it == loc[idx][search + offset].end() || *it >= r + 1)
                    continue;
                found = true;
                k = *it;
                break;
            }
            cout << k << '\n';
        }
    }
}
