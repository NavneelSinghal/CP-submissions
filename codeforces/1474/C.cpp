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
    n <<= 1;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(begin(a), end(a));
    for (int removed = 0; removed < n - 1; ++removed) {
        int cur_target = a[n - 1];
        int target = a[removed] + cur_target;
        multiset<int, greater<int>> rem;
        for (int i = 0; i < n - 1; ++i)
            if (i != removed)
                rem.insert(a[i]);
        vector<pair<int, int>> ans;
        ans.emplace_back(a[removed], cur_target);
        while (!rem.empty()) {
            int x = *rem.begin();
            rem.erase(rem.begin());
            auto it = rem.find(cur_target - x);
            if (it == rem.end()) break;
            rem.erase(it);
            ans.emplace_back(x, cur_target - x);
            cur_target = x;
        }
        if (rem.empty()) {
            cout << "YES\n";
            cout << target << '\n';
            for (auto &[x, y] : ans) 
                cout << x << ' ' << y << '\n';
            return;
        }
    }
    cout << "NO\n";
    return;
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

