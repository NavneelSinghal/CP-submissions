#include <bits/stdc++.h>
using namespace std;

namespace NTT {
  
    const int64_t MOD = (119 << 23) + 1; // 998244353
    const int64_t ROOT = 62;

    int64_t modpow(int64_t a, int64_t n) {
        int64_t ans = 1;
        while (n) {
            if (n & 1) ans = ans * a % MOD;
            a = a * a % MOD;
            n >>= 1;
        }
        return ans;
    }

    void ntt (vector<int64_t> &a) {
        
        int32_t n = a.size();
        int32_t L = 31 - __builtin_clz(n);

        static vector<int64_t> rt(2, 1);

        for (static int32_t k = 2, s = 2; k < n; k <<= 1, ++s) {
            rt.resize(n);
            int64_t z[] = {1, modpow(ROOT, MOD >> s)};
            for (int i = k; i < (k << 1); ++i) {
                rt[i] = rt[i >> 1] * z[i & 1] % MOD;
            }
        }

        vector<int32_t> rev(n);
        for (int32_t i = 0; i < n; ++i) {
            rev[i] = (rev[i >> 1] | ((i & 1) << L)) >> 1;
        }

        for (int32_t i = 0; i < n; ++i) {
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        for (int32_t k = 1; k < n; k <<= 1) {
            for (int32_t i = 0; i < n; i += (k << 1)) {
                for (int32_t j = 0; j < k; ++j) {
                    int64_t z = rt[j + k] * a[i + j + k] % MOD;
                    int64_t &ai = a[i + j];
                    a[i + j + k] = ai - z + ((z > ai) ? MOD : 0);
                    ai += ((ai + z >= MOD) ? (z - MOD) : z);
                }
            }
        }

    }

    vector<int64_t> conv(const vector<int64_t>& a, const vector<int64_t>& b, const int32_t max_pow = -1) {
        if (a.empty() || b.empty()) return {};
        int32_t s = a.size() + b.size() - 1;
        int32_t B = 32 - __builtin_clz(s);
        int32_t n = 1 << B;
        int32_t inv = modpow(n, MOD - 2);
        vector<int64_t> L(a), R(b), out(n);
        L.resize(n), R.resize(n);
        ntt(L);
        ntt(R);
        for (int32_t i = 0; i < n; ++i) {
            out[(-i) & (n - 1)] = ((((int64_t)L[i] * R[i]) % MOD) * inv) % MOD;
        }
        ntt(out);
        if (max_pow >= 0) s = min(s, max_pow + 1);
        return {out.begin(), out.begin() + s};
    }

}

int main() {
    int32_t n, s;
    cin >> n >> s;
    vector<int32_t> a(n);
    for (auto &x : a) cin >> x;

    function<vector<int64_t>(int32_t, int32_t)> multiply_many = [&] (int32_t l, int32_t r) {
        if (l > r) return vector<int64_t>(1, 1);
        if (l == r) {
            vector<int64_t> w(a[l] + 1);
            w[0] = 1;
            w[a[l]] = NTT::modpow(2, NTT::MOD - 2);
            return w;
        }
        int m = (l + r) >> 1;
        auto p = multiply_many(l, m);
        auto q = multiply_many(m + 1, r);
        return NTT::conv(p, q, s);
    };
    auto p = multiply_many(0, n - 1);
    cout << (NTT::modpow(2, n) * p[s]) % NTT::MOD << endl;
}
