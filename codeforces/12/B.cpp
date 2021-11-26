#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();

using ll = int64_t;
using ld = long double;

using namespace std;

int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string s, t;
        cin >> s >> t;
        auto it = min_element(begin(s), end(s), [](char a, char b) {
            if (a == '0') a = '9' + 1;
            if (b == '0') b = '9' + 1;
            return a < b;
        });
        if (it != begin(s)) swap(*it, *begin(s));
        sort(begin(s) + 1, end(s));
        if (s == t) {
            cout << "OK\n";
        } else {
            cout << "WRONG_ANSWER\n";
        }
    }
}
