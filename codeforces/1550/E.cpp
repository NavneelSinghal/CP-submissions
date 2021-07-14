#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

template <class T, bool unsafe = false>
constexpr uint32_t ctz(T a) {
    if constexpr (!unsafe) {
        if (!a) return sizeof(T) * 8;
    }
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return (uint32_t)(__builtin_ctz((uint32_t)a));
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return (uint32_t)(__builtin_ctzll((uint64_t)a));
    } else {
        static_assert(sizeof(T) == sizeof(uint64_t) * 2);
        uint32_t l = ctz((uint64_t)a);
        return l != sizeof(uint64_t) * 8
                   ? l
                   : l + ctz((uint64_t)(a >> sizeof(uint64_t) * 8));
    }
}

template <class T, bool unsafe = false>
constexpr uint32_t clz(T a) {
    if constexpr (!unsafe) {
        if (!a) return sizeof(T) * 8;
    }
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return (uint32_t)(__builtin_clz((uint32_t)a));
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return (uint32_t)(__builtin_clzll((uint64_t)a));
    } else {
        static_assert(sizeof(T) == sizeof(uint64_t) * 2);
        uint32_t l = clz((uint64_t)(a >> sizeof(uint64_t) * 8));
        return l != sizeof(uint64_t) * 8 ? l : l + clz((uint64_t)a);
    }
}

// -1 for 0
template <class T, bool unsafe = false>
constexpr uint32_t lg(T a) {
    if constexpr (sizeof(T) <= sizeof(uint32_t)) {
        return sizeof(uint32_t) * 8 - 1 - clz<T, unsafe>(a);
    } else if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return sizeof(uint64_t) * 8 - 1 - clz<T, unsafe>(a);
    } else {
        return sizeof(uint64_t) * 16 - 1 - clz<T, unsafe>(a);
    }
}

// split [l, r]
template <class Integer, class Predicate, bool type>
// __attribute__((target("bmi")))
Integer find_bin_split(Integer l, Integer r, const Predicate &pred) {
    if (l > r) {
        if constexpr (type)
            return r;
        else
            return r + 1;
    }
    ++r;
    Integer w = Integer(1) << lg<Integer, true>(r - l);
    --l;
    if (pred(l + w)) l = r - w;
    for (w >>= 1; w >= Integer(1); w >>= 1)
        if (pred(l + w)) l += w;
    if constexpr (type)
        return l;
    else
        return l + 1;
}

template <class Integer, class Predicate>
Integer find_first_false(Integer l, Integer r, const Predicate &pred) {
    return find_bin_split<Integer, Predicate, false>(l, r, pred);
}

template <class Integer, class Predicate>
Integer find_last_true(Integer l, Integer r, const Predicate &pred) {
    return find_bin_split<Integer, Predicate, true>(l, r, pred);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << find_last_true(1, n / k, [&](int m) {
            const int inf = 1e9;
            vector<vector<int>> leftmost(k, vector<int>(n + 1, inf));
            for (int bit = 0; bit < k; ++bit) {
                int prv = n;
                for (int i = n - 1; i >= 0; --i) {
                    leftmost[bit][i] = leftmost[bit][i + 1];
                    if (s[i] != '?' && s[i] != 'a' + bit) prv = i;
                    if (prv >= i + m) leftmost[bit][i] = i;
                }
            }
            vector<int> dp(1 << k, inf);
            dp[0] = 0;
            for (int mask = 0; mask < (1 << k); ++mask) {
                if (dp[mask] >= n) continue;
                for (int bit = 0; bit < k; ++bit)
                    if (!((mask >> bit) & 1))
                        dp[mask ^ (1 << bit)] = min(
                            dp[mask ^ (1 << bit)], leftmost[bit][dp[mask]] + m);
            }
            return dp[(1 << k) - 1] <= n;
        }) << '\n';
    }
}
