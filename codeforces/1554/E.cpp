#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,fma,mmx,bmi2")

#include <bits/stdc++.h>

using namespace std;

void solve();

signed main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    do {
        solve();
    } while (--t);
    return 0;
}

struct mod_int {
    static constexpr int MOD = 998244353;
    int value;

    mod_int(int i = 0) : value(i) {}

    mod_int operator+(const mod_int& m) const {
        mod_int lhs = *this;
        lhs += m;
        return lhs;
    }

    mod_int operator+=(const mod_int& m) {
        value += m.value;
        if (value >= MOD) value -= MOD;
        return value;
    }

    mod_int operator-(const mod_int& m) const {
        mod_int lhs = *this;
        lhs -= m;
        return lhs;
    }

    mod_int operator-=(const mod_int& m) {
        value -= (m.value - MOD);
        if (value >= MOD) value -= MOD;
        return value;
    }

    mod_int operator*(const mod_int& m) const {
        return (value * 1LL * m.value) % MOD;
    }

    mod_int operator*=(const mod_int& m) {
        value = (value * 1LL * m.value) % MOD;
        return value;
    }

    friend std::istream& operator>>(std::istream& is, mod_int& m) {
        is >> m.value;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const mod_int& m) {
        os << m.value;
        return os;
    }

    explicit operator int() const { return value; }
};

template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    // assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> divisors;
    for (int i = 2; i <= n; ++i)
        if ((n - 1) % i == 0) divisors.push_back(i);
    vector<mod_int> ans(n + 1);
    ans[1] = pwr(mod_int(2), n - 1);
    for (auto d : divisors) {
        vector<bool> right(n), minus(n);
        auto dfs = [&tree, &right, &minus, &d](auto&& self, int cur,
                                               int prev) -> void {
            int cnt = 0;
            for (auto next : tree[cur]) {
                if (next == prev) continue;
                self(self, next, cur);
                if (right[next])
                    cnt++;
                else if (!minus[next])
                    return;
            }
            const int D = cnt % d;
            if (D == 0) right[cur] = true;
            if (D == d - 1) minus[cur] = true;
        };
        dfs(dfs, 0, 0);
        if (right[0]) ans[d] = 1;
    }
    vector<vector<int>> dividers(n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 2 * i; j <= n; j += i) dividers[j].push_back(i);
    for (int i = n; i > 0; --i)
        for (auto d : dividers[i]) ans[d] -= ans[i];
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
}
