#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, a, b;
        cin >> n >> a >> b;
        string s;
        cin >> s;
        if (b > 0) {
            cout << 1LL * (a + b) * n << '\n';
        } else {
            vector<int> v;
            int cur = 0;
            int prv = -1;
            for (int i = 0; i < n; ++i) {
                if (s[i] == prv) {
                    cur++;
                } else {
                    if (cur) v.push_back(cur);
                    cur = 1;
                }
                prv = s[i];
            }
            v.push_back(cur);
            cout << 1LL * a * n + ((int)v.size() / 2 + 1) * b << '\n';
        }
    }
}
