#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n;
        m = n;
        map<int, int> a;
        while (n--) {
            int x;
            cin >> x;
            a[x]++;
        }
        cout << (m - (a.begin()->second)) << '\n';
    }
}
