#pragma GCC optimize ("Ofast")
//#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int32_t main() {

    fastio;

    int n, k;
    cin >> n >> k;
    int sum = 0, inv = 0;
    for (int i = 1; i <= k; ++i) {
        int a, b;
        cin >> a >> b;
        sum += b;
        inv += a * b;
        inv %= n;
    }
    if (sum < n) {
        cout << 1 << '\n';
    } else if (sum == n) {
        if (inv % n == (n * (n + 1) / 2) % n) cout << 1 << '\n';
        else cout << -1 << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;

}
