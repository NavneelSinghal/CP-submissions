#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;

struct Bitset {
    vector<uint64_t> bits;
    int N;
    int CAPACITY;
    Bitset(int n, bool bit = false) {
        N = n;
        CAPACITY = (n + 63) >> 6;
        uint64_t f = (bit ? -1 : 0);
        bits.assign(CAPACITY, f);
        if (n & 63) bits.back() &= (1ULL << (n & 63)) - 1;
    }
    void set(int x) { bits[x >> 6] |= (1ULL << (x & 63)); }
    bool get(int x) { return (bits[x >> 6] >> (x & 63)) & 1; }
    Bitset bitset_and(Bitset &o) {
        Bitset res(N);
        for (int i = 0; i < CAPACITY; ++i) res.bits[i] = (bits[i] & o.bits[i]);
        return res;
    }
    int count() {
        int ans = 0;
        for (int i = 0; i < CAPACITY; ++i) ans += __builtin_popcountll(bits[i]);
        return ans;
    }
};

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, p;
    cin >> n >> m >> p;

    vector<string> a(n);
    for (auto &x : a) cin >> x;

    vector<int> cnt(m);
    for (auto &x : a)
        for (int j = 0; j < m; ++j)
            if (x[j] == '1') cnt[j]++;

    const int threshold = (n + 1) >> 1;
    vector<Bitset> bitsets;
    vector<int> useful;

    for (int i = 0; i < m; ++i) {
        if (cnt[i] >= threshold) {
            useful.push_back(i);
            Bitset b(n);
            for (int j = 0; j < n; ++j)
                if (a[j][i] == '1') b.set(j);
            bitsets.push_back(std::move(b));
        }
    }

    const int sz = useful.size();

    auto rec = [&](const auto &self, Bitset &b, int i, unsigned mask) -> unsigned {
        if (i == sz) return mask;
        Bitset other = b.bitset_and(bitsets[i]);
        unsigned ans = mask;
        if (other.count() >= threshold)
            ans = self(self, other, i + 1, mask | (1U << i));
        unsigned ans2 = self(self, b, i + 1, mask);
        if (__builtin_popcount(ans) > __builtin_popcount(ans2)) return ans;
        return ans2;
    };

    Bitset b(n, 1);
    unsigned ans = rec(rec, b, 0, 0);

    uint64_t mask = 0;
    for (int i = 0; i < 30; ++i)
        if ((ans >> i) & 1) mask |= (1ULL << useful[i]);

    for (int i = 0; i < m; ++i) cout << ((mask >> i) & 1);
    cout << '\n';
}
