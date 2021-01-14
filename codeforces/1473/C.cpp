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

int merge_ranges(int a, int b, int c, int d) {
    assert(a <= b);
    assert(c <= d);
    if (c < a) {
        swap(a, c);
        swap(b, d);
    }
    // a <= c
    if (b < c) {
        return b - a + 1 + d - c + 1;
    } else {
        return max(b, d) - a + 1;
    }
}

void solve(int _) {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    int cur = k;
    for (int i = k - 1 - (n - k); i <= k - 1; ++i) {
        a[i] = cur--;
    }
    for (int i = k - 1 - (n - k) - 1; i >= 0; --i) {
        a[i] = cur--;
    }
    for (auto &x : a) cout << x << ' ';
    cout << '\n';
}

void brute(int _) {
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    
    for (int i = 0; i < k; ++i) {
        a[i] = i;
    }
    for (int i = k; i < n; ++i) {
        a[i] = k - 2 - (i - k);
    }
    
    long long max_inv = (n - k) * (n - k);

    vector<int> best_b = a;

    vector<int> cur(k);
    iota(cur.begin(), cur.end(), 1);
    
    vector<int> best_permutation = cur;
    
    do {
        
        vector<int> w(n);
        for (int i = 0; i < n; ++i) {
            w[i] = cur[a[i]];
        }
        
        long long inv = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                inv += w[i] > w[j];
            }
        }

        if (inv <= max_inv) {
            if (best_b < w) {
                best_b = w;
                best_permutation = cur;
            }
        }
    } while (next_permutation(cur.begin(), cur.end()));
    for (auto &x : best_permutation) cout << x << ' ';
    cout << endl;
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
