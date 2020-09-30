#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<vector<int>> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
    }
    vector<int> lens(n + 1, 1e9);
    for (int i = 0; i <= n; ++i) {
        // find the smallest k such that i is the smallest element common to each subarray of size k
        if (pos[i].empty()) {
            continue;
        }
        vector<int> v = pos[i];
        int ans = max(v.front() + 1, n - v.back());
        for (int j = 0; j + 1 < (int) v.size(); ++j) {
            ans = max(ans, v[j + 1] - v[j]);
        }
        lens[ans] = min(lens[ans], i);
    }
    for (int i = 0; i < n; ++i) {
        lens[i + 1] = min(lens[i], lens[i + 1]);
    }
    for (int i = 1; i <= n; ++i) {
        if (lens[i] == 1e9) lens[i] = -1;
        cout << lens[i] << ' ';
    }
    cout << '\n';

}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
