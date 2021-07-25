#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

using ll = int64_t;

template <class T, bool unsafe = false>
uint32_t ctz(T a) {
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
uint32_t clz(T a) {
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
uint32_t lg(T a) {
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

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        int n, k;
        cin >> n >> k;
        vector<ll> p(n);
        for (auto &x : p) cin >> x;
        ll l = 0, r = 1e15;
        cout << find_first_false(l, r, [&](ll m) {
            ll price = m + p[0];
            bool works = true;
            for (int i = 1; i < n; ++i) {
                if (price * k < 100 * p[i]) {
                    works = false;
                    break;
                }
                price += p[i];
            }
            return !works;
        }) << '\n';
    }
}