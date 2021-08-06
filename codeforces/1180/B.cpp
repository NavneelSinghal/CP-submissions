#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) {
            cin >> x;
            if (x >= 0) (x *= -1) -= 1;
        }
        if (n & 1) (*min_element(begin(a), end(a)) *= -1) -= 1;
        for (auto x : a) cout << x << ' ';
        cout << '\n';
    }
}

