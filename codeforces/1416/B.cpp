#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int sum = 0;
    for (auto x : a) sum += x;
    if (sum % n != 0) {
        cout << -1 << '\n';
        return;
    }
    vector<pair<pair<int, int>, int>> v;
    auto work = [&] (int i, int j, int x) {
        a[i] -= i * x;
        a[j] += i * x;
        v.push_back(make_pair(make_pair(i, j), x));
    };
    int target = sum / n;
    for (int i = 2; i <= n; ++i) {
        work(1, i, (i - a[i] + 1'000'000'000LL * i) % i);
        work(i, 1, a[i] / i);
    }
    for (int i = 2; i <= n; ++i) {
        work(1, i, target);
    }
    cout << v.size() << '\n';
    for (auto p : v) {
        cout << p.first.first << ' ' << p.first.second << ' ' << p.second << '\n';
    }
    return;
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
