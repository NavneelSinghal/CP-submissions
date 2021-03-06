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
[[nodiscard]] bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
[[nodiscard]] bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

template <typename T> void ignore_unused(const T&) {}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

constexpr int mod = 998244353;
// constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, int64_t n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {
}

void solve(int) {
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), b(n);
    long long sum = 0;
    
    for (auto &x : a) cin >> x, sum += x;
    for (auto &x : b) cin >> x;
    
    if (sum < m) {
        cout << -1 << '\n';
        return;
    }
    
    vector<int> imp, reg;
    for (int i = 0; i < n; ++i) {
        if (b[i] == 1) {
            reg.push_back(a[i]);
        } else {
            imp.push_back(a[i]);
        }
    }
    
    sort(rbegin(reg), rend(reg));
    sort(rbegin(imp), rend(imp));

    vector<long long> prer(1 + reg.size());
    vector<long long> prei(1 + imp.size());
    long long p = 0;
    for (int i = 0; i < reg.size(); ++i) {
        p += reg[i];
        prer[i + 1] = p;
    }
    
    p = 0;
    
    for (int i = 0; i < imp.size(); ++i) {
        p += imp[i];
        prei[i + 1] = p;
    }

    long long best = 1e9;

    for (int i = 0; i < prer.size(); ++i) {
        auto it = lower_bound(begin(prei), end(prei), m - prer[i]);
        if (it == end(prei)) {
            continue;
        } else {
            best = min(best, 2LL * (it - begin(prei)) + i);
        }
    }

    cout << best << '\n';

}

void brute(int) {
}

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

