#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 2e9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll t = 1;
    cin >> t;
    while (t--) {
        map<string, pair<string, ll>> a;
        string last;
        int n;
        cin >> n;
        auto count = [](string s) {
            ll ans = 0;
            for (int i = 0; i + 4 <= s.size(); ++i) {
                ans += s.substr(i, 4) == "haha";
            }
            return ans;
        };
        auto merge = [](pair<string, ll> p, pair<string, ll> q) {
            ll cnt = p.second + q.second;
            string store = p.first + q.first;
            for (int i = max(0, int(p.first.size()) - 3);
                 i <= int(store.size()) - 4 && i < int(p.first.size()); ++i) {
                cnt += store.substr(i, 4) == "haha";
            }
            if (store.size() >= 6) store.erase(begin(store) + 3, end(store) - 3);
            return pair{store, cnt};
        };
        while (n--) {
            string x, y, z, w;
            cin >> x >> y;
            if (y == ":=") {
                cin >> z;
                a[x] = {z, count(z)};
            } else {
                cin >> z >> y >> w;
                a[x] = merge(a[z], a[w]);
            }
            last = x;
        }
        cout << a[last].second << '\n';
    }
}
