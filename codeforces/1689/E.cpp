#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

struct dsu {
    int n;
    vector<int> par;

    // negative - size
    dsu(int n) : n(n), par(n, -1) {}

    int root(int v) {
        if (par[v] < 0) return v;
        return par[v] = root(par[v]);
    }

    bool join(int a, int b) {
        a = root(a);
        b = root(b);
        if (a != b) {
            if (par[b] < par[a]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
        return false;
    }

    int size(int a) {
        a = root(a);
        return -par[a];
    }

    auto components() {
        vector<int> roots(n), size(n);
        for (int i = 0; i < n; ++i) {
            roots[i] = root(i);
            size[roots[i]]++;
        }
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; ++i) ans[i].reserve(size[i]);
        for (int i = 0; i < n; ++i) ans[roots[i]].push_back(i);
        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const auto& v) { return v.empty(); }),
                  ans.end());
        return ans;
    }

    int count_components() {
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (root(i) == i) ans++;
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        auto check = [&](const auto& a) {
            int n = (int)a.size();
            dsu d(n);
            for (int bit = 0; bit < 31; ++bit) {
                int last = -1;
                for (int i = 0; i < n; ++i) {
                    if (a[i] >> bit & 1) {
                        if (last == -1)
                            last = i;
                        else
                            d.join(i, last);
                    }
                }
            }
            int r = d.root(0), x = 0;
            for (int i = 0; i < n; ++i)
                if (d.root(i) == r) ++x;
            return x == n;
        };
        auto incr = [](auto a, int pos, int val) {
            a[pos] += val;
            return a;
        };
        auto print = [](int m, const auto& a) {
            cout << m << '\n';
            for (auto x : a) cout << x << ' ';
            cout << '\n';
        };
        int moves = 0;
        for (auto& x : a)
            if (x == 0) ++x, ++moves;
        if (check(a)) {
            print(moves, a);
        } else {
            vector<int> A;
            bool works = false;
            for (auto add : {-1, +1}) {
                if (works) break;
                for (int i = 0; i < n; ++i) {
                    A = incr(a, i, add);
                    if (check(A)) {
                        print(moves + 1, A);
                        works = true;
                        break;
                    }
                }
            }
            if (!works) {
                vector<int> pos;
                int mx = 0;
                for (int i = 0; i < n; ++i) {
                    int p = a[i] & -a[i];
                    if (p > mx)
                        pos = {i}, mx = p;
                    else if (p == mx)
                        pos.push_back(i);
                }
                assert(pos.size() > 1);
                a[pos[0]]--;
                a[pos[1]]++;
                print(moves + 2, a);
            }
        }
    }
}

