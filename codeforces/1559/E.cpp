#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>
using namespace std;

#define loop(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define loopr(i, a, b) for (int i = (int)a; i >= (int)b; --i)
constexpr int MOD = 998244353;

int dp[50][100001];

template <int N = 100'000>
struct MU {
    int primes[N + 1]{}, mu[N + 1]{}, sqfree[N + 1]{};
    char is_prime[N + 1]{};
    constexpr MU() {
        for (int i = 0; i <= N; ++i) is_prime[i] = 1;
        is_prime[0] = is_prime[1] = false;
        mu[1] = 1;
        int loc = 0;
        for (int i = 2; i <= N; ++i) {
            if (is_prime[i]) mu[i] = -1, primes[loc++] = i;
            for (int j = 0; j < loc && i * primes[j] <= N; ++j) {
                is_prime[i * primes[j]] = false;
                if (i % primes[j] == 0) {
                    mu[i * primes[j]] = 0;
                    break;
                } else {
                    mu[i * primes[j]] = -mu[i];
                }
            }
        }
        // special case
        loc = 0;
        sqfree[loc++] = 1;
        for (int i = 2; i <= N; ++i)
            if (mu[i]) sqfree[loc++] = i;
        sqfree[loc++] = 1e9;
    }
};

static constexpr MU mu;

inline void add(int& a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

inline void sub(int& a, int b) {
    a += MOD - b;
    if (a >= MOD) a -= MOD;
}

void testcases(int test) {
    int n, mm;
    cin >> n >> mm;
    vector<array<int, 2>> aa(n);
    loop(i, 0, n) cin >> aa[i][0] >> aa[i][1];
    vector<int> num(mm + 1);
    for (auto div : mu.sqfree) {
        int m = mm / div;
        if (m == 0) break;
        vector<array<int, 2>> a = aa;
        loop(i, 0, n) {
            a[i][1] /= div;
            a[i][0] = (a[i][0] + div - 1) / div;
            a[i][1] -= a[i][0];
            m -= a[i][0];
        }
        if (m < 0) continue;
        loop(i, 0, a[0][1] + 1) dp[0][i] = 1;
        loop(i, 1, n) {
            loop(j, 1, m + 1) add(dp[i - 1][j], dp[i - 1][j - 1]);
            loop(j, 0, m + 1) {
                int r = (j - a[i][1] >= 1) ? dp[i][j - a[i][1] - 1] : 0;
                dp[i][j] = dp[i - 1][j];
                sub(dp[i][j], r);
                if (i == n - 1) add(num[div], dp[n - 1][j]);
            }
        }
    }
    loopr(i, mm, 1) for (int j = 2 * i; j <= mm; j += i) sub(num[i], num[j]);
    cout << num[1] << '\n';
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    loop(i, 0, t) testcases(i);
}
