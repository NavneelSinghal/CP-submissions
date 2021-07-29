#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n;
        cin >> n;
        string ans;
        if (n == 1) {
            ans = "a";
        } else if (n % 2) {
            ans = string((n - 1) / 2, 'a') + "bc" + string((n - 3) / 2, 'a');
        } else {
            ans = string(n / 2, 'a') + "b" + string((n - 2) / 2, 'a');
        }
        cout << ans << '\n';
    }
}

