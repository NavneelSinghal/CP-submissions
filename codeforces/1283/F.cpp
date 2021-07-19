#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        vector<int> a(n - 1);
        for (auto &x : a) cin >> x, --x;
        vector<int> vis(n);
        cout << a[0] + 1 << '\n';
        int cur_max = n - 1;
        for (int i = 0; i + 1 < n; ++i) {
            vis[a[i]] = 1;
            while (vis[cur_max]) --cur_max;
            if (i == n - 2 || vis[a[i + 1]]) {
                cout << a[i] + 1 << ' ' << cur_max + 1 << '\n';
                vis[cur_max] = 1;
            } else {
                cout << a[i + 1] + 1 << ' ' << a[i] + 1 << '\n';
            }
        }
    }
}
