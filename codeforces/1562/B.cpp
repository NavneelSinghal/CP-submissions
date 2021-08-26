#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;

using ll = int64_t;
using ld = long double;

// memory - n + n/(log n)
// how to compute a multiplicative function in o(n) for all values
template <int n = 1'000'000>
struct fast_sieve_func_optimized {
    vector<int> primes, func;
    vector<char> is_prime;
    fast_sieve_func_optimized() {
        is_prime.assign(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        func.resize(n + 1);
        func[1] = 1;  // for multiplicative functions, it is either 0 or 1
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                // here you should handle the case of primes by updating func[i]
            }
            for (auto p : primes) {
                if (i * p > n) break;
                is_prime[i * p] = false;
                // update func[i * p] in the following branches
                // or maintain the smallest prime factor and check using that
                if (i % p == 0) {
                    // p divides i
                    // see how to update here
                    break;
                } else {
                    // p and i are coprime
                    // see how to update here
                }
            }
        }
    }
};

fast_sieve_func_optimized<> sieve;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) a[i] = s[i] - '0';
        bool found = false;
        for (auto x : a) {
            if (x != 2 && x != 3 && x != 5 && x != 7) {
                cout << 1 << '\n';
                cout << x << '\n';
                found = true;
                break;
            }
        }
        if (found) continue;
        vector<int> freq(30);
        for (auto x : a) freq[x]++;
        for (auto x : a) if (freq[x] > 1) {
            cout << 2 << '\n';
            cout << x << x << '\n';
            found = true;
            break;
        }
        if (found) continue;
        assert(n > 0 && n <= 4);
        int ans = 100;
        int print = 0;
        for (int i = 0; i < (1 << n); ++i) {
            int num = 0;
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    num *= 10;
                    num += a[j];
                }
            }
            if (num != 0) {
                if (!sieve.is_prime[num]) {
                    if (ans > __builtin_popcount(i)) {
                        ans = __builtin_popcount(i);
                        print = num;
                    }
                }
            }
        }
        assert(ans != 100);
        cout << ans << '\n';
        cout << print << '\n';
    }
}

