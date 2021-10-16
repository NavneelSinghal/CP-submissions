#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#endif

#include "bits/stdc++.h"
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif

using ll = int64_t;
using ld = long double;

using namespace std;

// memory - 3n + n/(log n)
template <int n = 1'000'000>
struct fast_sieve_func_spf {
    vector<int> primes, spf;
    vector<char> is_prime;
    vector<int> ans;
    fast_sieve_func_spf() {
        is_prime.assign(n + 1, true);
        ans.assign(n + 1, 0);
        is_prime[0] = is_prime[1] = false;
        spf.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            ans[i] = ans[i - 1];
            int x = (int)sqrt(i);
            if (x * x == i and is_prime[x]) ans[i]--;
            if (is_prime[i]) {
                primes.push_back(i);
                spf[i] = i;
                ++ans[i];
            }
            int spfi = spf[i];
            for (const auto p : primes) {
                const int k = i * p;
                if (k > n) break;
                is_prime[k] = false;
                // p <= spfi
                spf[k] = p;
                if (spfi == p) break;
            }
        }
    }
};

fast_sieve_func_spf<> s;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(6) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        cout << s.ans[n] + 1 << '\n';
    }
}
