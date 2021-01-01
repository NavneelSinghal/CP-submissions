#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename X, typename Y> 
X& remin(X& x, const Y& y) { return x = (y < x) ? y : x; }

template<typename X, typename Y>
X& remax(X& x, const Y& y) { return x = (x < y) ? y : x; }

template<typename X, typename Y>
bool ckmin(X& x, const Y& y) { return (y < x) ? (x = y, 1) : 0; }

template<typename X, typename Y>
bool ckmax(X& x, const Y& y) { return (x < y) ? (x = y, 1) : 0; }

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0)
        return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
}

// const int mod = 998244353;
const int mod = 1e9 + 7;
const long long linf = 3e18;

long long pwr_mod(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

template <typename T>
T pwr(T a, long long n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

long long power_overflow(long long a, long long n) {
    long long ans = 1;
    while (n) {
        if (n & 1) {
            if (ans < linf / a) ans *= a;
            else return linf;
        }
        if (n > 1) {
            if (a < linf / a) a *= a;
            else return linf;
        }
        n >>= 1;
    }
    return ans;
}

inline long long isqrt(long long n) {
    long long sq = (long long) sqrtl((long double) n) - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) sq++;
    if ((sq * sq) == n) return sq;
    return sq - 1;
}


template <int N = 1'000'000>
struct MU {
    vector<int> primes, mu;
    vector<char> is_prime;
    MU() {
        is_prime.assign(N + 1, true);
        is_prime[0] = is_prime[1] = false;
        mu.resize(N + 1);
        mu[1] = 1;
        for (int i = 2; i <= N; ++i) {
            if (is_prime[i]) mu[i] = -1, primes.push_back(i);
            for (int j = 0; j < (int) primes.size() && i * primes[j] <= N; ++j) {
                is_prime[i * primes[j]] = false;
                if (i % primes[j] == 0) {
                    mu[i * primes[j]] = 0;
                    break;
                } else {
                    mu[i * primes[j]] = -mu[i];
                }
            }
        }
    }
};

struct KthRoot {
    using u32 = unsigned int;
    using u64 = unsigned long long int;
    vector<u64> pow[65]; // pow[k][x] = pow(x+2,k)  (k >= 4)
    KthRoot() {
        for (u32 t = 2; t < (1<<16); t++) {
            u64 s = t*t; s = s*s;
            for (int k = 4; ; k++) {
                pow[k].push_back(s);
                if (__builtin_umulll_overflow(s,t,&s)) break;
            }
        }
    }
    u64 sqrt(u64 n) const {
        if (n == -1ull) return u32(-1);
        u64 x = std::sqrt((double)n);
        return x*x > n ? x-1 : x;
    }
    u64 cbrt(u64 n) const {
        u64 x = 0, y = 0;
        for (int s = 63; s >= 0; s -= 3) {
            x <<= 1;
            y = 3*x*(x+1)+1;
            if (y <= (n>>s)) n -= y<<s, ++x;
        }
        return x;
    }
    u64 operator()(u64 n, int k) {
        assert(k >= 1);
        if (k == 1 || n == 0) return n;
        if (k == 2) return sqrt(n);
        if (k == 3) return cbrt(n);
        auto ub = upper_bound(pow[k].begin(), pow[k].end(), n);
        return (ub-pow[k].begin())+1;
    }
};

KthRoot k;
MU<64> m;

void precompute() {
}

void solve(int _) {
    long long n;
    cin >> n;
    long long cnt = 0;
    for (int i = 1; i < 61; ++i) {
        cnt += m.mu[i] * (k(n, i) - 1);
    }
    cout << cnt << '\n';
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
