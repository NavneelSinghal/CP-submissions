#pragma GCC optimize ("Ofast")
//#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

template <int N = 1'000'001>
struct fast_sieve {
    vector<int> primes;
    vector<char> is_prime;
    vector<int> pi;
    fast_sieve() {
        is_prime.assign(N + 1, true);
        pi.assign(N + 1, 0);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= N; ++i) {
            if (is_prime[i]) primes.push_back(i);
            for (int j = 0; j < primes.size() && i * primes[j] <= N; ++j) {
                is_prime[i * primes[j]] = false;
                if (i % primes[j] == 0) break;
            }
        }
        for (int i = 1; i <= N; ++i) {
            pi[i] = pi[i - 1] + is_prime[i];
        }
    }
};

int32_t main() {

    fastio;

    fast_sieve<> s;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int x = sqrtl(n);
        cout << 1 + s.pi[n] - s.pi[x] << '\n';
    }

    return 0;
}
