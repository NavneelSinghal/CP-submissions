#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    uint32_t mod;
    cin >> n >> mod;
    uint32_t mod2 = mod << 1;
    uint32_t r;
    {
        uint32_t iv = mod;
        for (uint32_t i = 0; i != 4; ++i) iv *= 2U - mod * iv;
        r = -iv;
    }
    uint32_t r2 = -uint64_t(mod) % mod;
    auto reduce = [&mod, &r](uint64_t x) {
        return (x + uint64_t(uint32_t(x) * r) * mod) >> 32;
    };
    auto norm = [&mod](uint32_t x) {
        return x - (mod & -(x >= mod));
    };
    auto make = [&reduce, &r2](uint32_t x) {
        return reduce(uint64_t(x) * r2);
    };
    auto get = [&norm, &reduce](uint32_t x) {
        return norm(reduce(x));
    };
    auto add = [&mod2](uint32_t& x, uint32_t v) {
        x += v - mod2;
        x += mod2 & -(x >> 31);
    };
    auto sub = [&mod2](uint32_t& x, uint32_t v) {
        x -= v;
        x += mod2 & -(x >> 31);
    };
    vector<uint32_t> ans(2 * n + 2);
    auto update = [&add, &sub, &ans](int l, int r, int v) {
        add(ans[l], v);
        sub(ans[r + 1], v);
    };
    update(1, 1, make(1));
    for (int i = 1; i <= n; ++i) {
        add(ans[i], ans[i - 1]);
        auto cur = ans[i];
        update(i + 1, n, cur);
        for (int j = 2; j * (i + 1) - 1 < 2 * n && j * i <= n; j++)
            update(j * i, j * (i + 1) - 1, cur);
    }
    cout << get(ans[n]) << '\n';
}

