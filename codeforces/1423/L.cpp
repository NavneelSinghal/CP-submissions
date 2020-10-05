#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ull unsigned long long

using bt = bitset<1024>;
 
int32_t main() {
    int n, s, d;
    cin >> n >> s >> d;
    vector<bt> a(s);
    
    for (auto &x : a) {
        int k;
        cin >> k;
        while (k--) {
            int w;
            cin >> w;
            --w;
            x[w] = 1;
        }
    }
    
    int half = 2 * s / 3;
    
    // subset, answer
    const int W = 19197233;
    vector<pair<int, int>> v(1 << half);
    for (int mask = 0; mask < (1 << half); ++mask) {
        bt x;
        for (int i = 0; i < half; ++i) {
            if (mask & (1 << i)) {
                x ^= a[i];
            }
        }
        int hash = 0;
        ull* z = (ull*) &x;
        for (int i = 0; i < (1024 >> 6); ++i) {
            hash = hash * W + z[i];
        }
        v[mask] = make_pair(hash, __builtin_popcount(mask));
    }

    sort(v.begin(), v.end());
    while (d--) {
        int k;
        cin >> k;
        bt xx;
        while (k--) {
            int w;
            cin >> w;
            --w;
            xx[w] = 1;
        }
        int ans = 1e9;
        for (int mask = 0; mask < (1 << (s - half)); ++mask) {
            bt x = xx;
            for (int i = half; i < s; ++i) {
                if (mask & (1 << (i - half))) {
                    x ^= a[i];
                }
            }
            int hash = 0;
            ull* z = (ull*) &x;
            for (int i = 0; i < (1024 >> 6); ++i) {
                hash = hash * W + z[i];
            }
            auto it = lower_bound(v.begin(), v.end(), make_pair(hash, -1LL));
            if (it != v.end() && it->first == hash) {
                ans = min(ans, it->second + __builtin_popcount(mask));
            }
        }
        if (ans == 1e9) cout << -1 << '\n';
        else cout << ans << '\n';
    }

}
