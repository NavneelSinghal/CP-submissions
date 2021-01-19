#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename X, typename Y>
X &remin(X &x, const Y &y) {
    return x = (y < x) ? y : x;
}

template <typename X, typename Y>
X &remax(X &x, const Y &y) {
    return x = (x < y) ? y : x;
}

template <typename X, typename Y>
bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
}

const int mod = 998244353;
// const int mod = 1e9 + 7;
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

// when using integers, keep overflow in mind
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

template <int N = 1'000'000>
struct sieve {
    vector<char> is_prime;
    vector<int> primes;
    sieve() {
        is_prime.assign(N + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= N; ++i)
            if (is_prime[i])
                for (int j = i * i; j <= N; j += i) is_prime[j] = false;
        for (int i = 2; i <= N; ++i)
            if (is_prime[i]) primes.push_back(i);
    }
};

sieve<> s;

void precompute() {
}

void solve(int _) {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (n == 2) {
        if (a[1] == a[2]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        vector<int> pre(n + 2, -1), suf(n + 2, -1);
        pre[0] = 0, pre[1] = a[1], suf[n + 1] = 0, suf[n] = a[n];
        for (int i = 2; i <= n; ++i) {
            if (a[i] >= pre[i - 1]) {
                pre[i] = a[i] - pre[i - 1];
            } else {
                break;
            }
        }
        for (int i = n - 1; i > 0; --i) {
            if (suf[i + 1] <= a[i]) {
                suf[i] = a[i] - suf[i + 1];
            } else {
                break;
            }
        }
        auto works = [&] (int a, int b, int c, int d) {
            if (a == -1 || d == -1 || b < a || c < d) return false;
            return b + d == a + c;
        };
        for (int i = 1; i < n; ++i) {
            if (works(pre[i - 1], a[i], a[i + 1], suf[i + 2])
                || works(pre[i - 1], a[i + 1], a[i], suf[i + 2])) {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
        return;
    }
}

void brute(int _) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */

