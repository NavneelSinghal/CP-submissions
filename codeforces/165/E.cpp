#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n; cin >> n;
    int m = 22;
    vector<unsigned> dp((1 << m), UINT_MAX);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        dp[a[i]] = a[i];
    }
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < (1 << m); ++mask) {
            dp[mask | (1 << i)] = min(dp[mask], dp[mask | (1 << i)]);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (int) dp[~a[i] & ((1 << m) - 1)] << " ";
    }
    cout << endl;
}
