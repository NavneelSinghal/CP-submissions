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

void precompute() {}

int sqfree(int n) {
    int ans = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans *= i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    return ans * n;
}

const int maxn = 300000 + 10;

void solve(int _) {

    int n;
    cin >> n;
    
    set<int> s;
    vector<int> a(n);

    int g = 0;

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (x == 1) {
            cout << 1 << endl;
            return;
        }
        x = sqfree(x);
        g = __gcd(g, x);
        s.insert(x);
    }

    if (g != 1) {
        cout << -1 << endl;
        return;
    }

    n = s.size();
    a = vector<int>(s.begin(), s.end());
    
    for (auto &x : a) {
        for (int i = 2 * x; i < maxn; i += x) {
            auto it = s.find(i);
            if (it != s.end()) {
                s.erase(it);
            }
        }
    }

    a = vector<int>(s.begin(), s.end());

    for (int i = 2; ; ++i) {
        set<int> ss;
        for (auto &x : s) {
            for (auto &w : a) {
                ss.insert(__gcd(w, x));
            }
        }
        if (ss.find(1) != ss.end()) {
            cout << i << '\n';
            return;
        }
        s = ss;
    }
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
