#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

template <class Integer, class F>
Integer find_first_false(Integer l, Integer r,
                         F&& f) requires(sizeof(Integer) == 8) {
    if (l > r) return r + 1;
    ++r;
    int p = __lg(r - l);
    Integer w = Integer(1) << p;
    --l;
    if (f(l + w)) l = r - w;
    switch (p) {
        case 63:
            if (f(l + (1LL << 62))) l += (1LL << 62);
        case 62:
            if (f(l + (1LL << 61))) l += (1LL << 61);
        case 61:
            if (f(l + (1LL << 60))) l += (1LL << 60);
        case 60:
            if (f(l + (1LL << 59))) l += (1LL << 59);
        case 59:
            if (f(l + (1LL << 58))) l += (1LL << 58);
        case 58:
            if (f(l + (1LL << 57))) l += (1LL << 57);
        case 57:
            if (f(l + (1LL << 56))) l += (1LL << 56);
        case 56:
            if (f(l + (1LL << 55))) l += (1LL << 55);
        case 55:
            if (f(l + (1LL << 54))) l += (1LL << 54);
        case 54:
            if (f(l + (1LL << 53))) l += (1LL << 53);
        case 53:
            if (f(l + (1LL << 52))) l += (1LL << 52);
        case 52:
            if (f(l + (1LL << 51))) l += (1LL << 51);
        case 51:
            if (f(l + (1LL << 50))) l += (1LL << 50);
        case 50:
            if (f(l + (1LL << 49))) l += (1LL << 49);
        case 49:
            if (f(l + (1LL << 48))) l += (1LL << 48);
        case 48:
            if (f(l + (1LL << 47))) l += (1LL << 47);
        case 47:
            if (f(l + (1LL << 46))) l += (1LL << 46);
        case 46:
            if (f(l + (1LL << 45))) l += (1LL << 45);
        case 45:
            if (f(l + (1LL << 44))) l += (1LL << 44);
        case 44:
            if (f(l + (1LL << 43))) l += (1LL << 43);
        case 43:
            if (f(l + (1LL << 42))) l += (1LL << 42);
        case 42:
            if (f(l + (1LL << 41))) l += (1LL << 41);
        case 41:
            if (f(l + (1LL << 40))) l += (1LL << 40);
        case 40:
            if (f(l + (1LL << 39))) l += (1LL << 39);
        case 39:
            if (f(l + (1LL << 38))) l += (1LL << 38);
        case 38:
            if (f(l + (1LL << 37))) l += (1LL << 37);
        case 37:
            if (f(l + (1LL << 36))) l += (1LL << 36);
        case 36:
            if (f(l + (1LL << 35))) l += (1LL << 35);
        case 35:
            if (f(l + (1LL << 34))) l += (1LL << 34);
        case 34:
            if (f(l + (1LL << 33))) l += (1LL << 33);
        case 33:
            if (f(l + (1LL << 32))) l += (1LL << 32);
        case 32:
            if (f(l + (1LL << 31))) l += (1LL << 31);
        case 31:
            if (f(l + (1LL << 30))) l += (1LL << 30);
        case 30:
            if (f(l + (1LL << 29))) l += (1LL << 29);
        case 29:
            if (f(l + (1LL << 28))) l += (1LL << 28);
        case 28:
            if (f(l + (1LL << 27))) l += (1LL << 27);
        case 27:
            if (f(l + (1LL << 26))) l += (1LL << 26);
        case 26:
            if (f(l + (1LL << 25))) l += (1LL << 25);
        case 25:
            if (f(l + (1LL << 24))) l += (1LL << 24);
        case 24:
            if (f(l + (1LL << 23))) l += (1LL << 23);
        case 23:
            if (f(l + (1LL << 22))) l += (1LL << 22);
        case 22:
            if (f(l + (1LL << 21))) l += (1LL << 21);
        case 21:
            if (f(l + (1LL << 20))) l += (1LL << 20);
        case 20:
            if (f(l + (1LL << 19))) l += (1LL << 19);
        case 19:
            if (f(l + (1LL << 18))) l += (1LL << 18);
        case 18:
            if (f(l + (1LL << 17))) l += (1LL << 17);
        case 17:
            if (f(l + (1LL << 16))) l += (1LL << 16);
        case 16:
            if (f(l + (1LL << 15))) l += (1LL << 15);
        case 15:
            if (f(l + (1LL << 14))) l += (1LL << 14);
        case 14:
            if (f(l + (1LL << 13))) l += (1LL << 13);
        case 13:
            if (f(l + (1LL << 12))) l += (1LL << 12);
        case 12:
            if (f(l + (1LL << 11))) l += (1LL << 11);
        case 11:
            if (f(l + (1LL << 10))) l += (1LL << 10);
        case 10:
            if (f(l + (1LL << 9))) l += (1LL << 9);
        case 9:
            if (f(l + (1LL << 8))) l += (1LL << 8);
        case 8:
            if (f(l + (1LL << 7))) l += (1LL << 7);
        case 7:
            if (f(l + (1LL << 6))) l += (1LL << 6);
        case 6:
            if (f(l + (1LL << 5))) l += (1LL << 5);
        case 5:
            if (f(l + (1LL << 4))) l += (1LL << 4);
        case 4:
            if (f(l + (1LL << 3))) l += (1LL << 3);
        case 3:
            if (f(l + (1LL << 2))) l += (1LL << 2);
        case 2:
            if (f(l + (1LL << 1))) l += (1LL << 1);
        case 1:
            if (f(l + (1LL << 0))) l += (1LL << 0);
        default:
            break;
    }
    return l + 1;
}

template <class Integer, class F>
Integer find_first_false(Integer l, Integer r,
                         F&& f) requires(sizeof(Integer) == 4) {
    if (l > r) return r + 1;
    ++r;
    int p = __lg(r - l);
    Integer w = Integer(1) << p;
    --l;
    if (f(l + w)) l = r - w;
    switch (p) {
        case 31:
            if (f(l + (1 << 30))) l += 1 << 30;
        case 30:
            if (f(l + (1 << 29))) l += 1 << 29;
        case 29:
            if (f(l + (1 << 28))) l += 1 << 28;
        case 28:
            if (f(l + (1 << 27))) l += 1 << 27;
        case 27:
            if (f(l + (1 << 26))) l += 1 << 26;
        case 26:
            if (f(l + (1 << 25))) l += 1 << 25;
        case 25:
            if (f(l + (1 << 24))) l += 1 << 24;
        case 24:
            if (f(l + (1 << 23))) l += 1 << 23;
        case 23:
            if (f(l + (1 << 22))) l += 1 << 22;
        case 22:
            if (f(l + (1 << 21))) l += 1 << 21;
        case 21:
            if (f(l + (1 << 20))) l += 1 << 20;
        case 20:
            if (f(l + (1 << 19))) l += 1 << 19;
        case 19:
            if (f(l + (1 << 18))) l += 1 << 18;
        case 18:
            if (f(l + (1 << 17))) l += 1 << 17;
        case 17:
            if (f(l + (1 << 16))) l += 1 << 16;
        case 16:
            if (f(l + (1 << 15))) l += 1 << 15;
        case 15:
            if (f(l + (1 << 14))) l += 1 << 14;
        case 14:
            if (f(l + (1 << 13))) l += 1 << 13;
        case 13:
            if (f(l + (1 << 12))) l += 1 << 12;
        case 12:
            if (f(l + (1 << 11))) l += 1 << 11;
        case 11:
            if (f(l + (1 << 10))) l += 1 << 10;
        case 10:
            if (f(l + (1 << 9))) l += 1 << 9;
        case 9:
            if (f(l + (1 << 8))) l += 1 << 8;
        case 8:
            if (f(l + (1 << 7))) l += 1 << 7;
        case 7:
            if (f(l + (1 << 6))) l += 1 << 6;
        case 6:
            if (f(l + (1 << 5))) l += 1 << 5;
        case 5:
            if (f(l + (1 << 4))) l += 1 << 4;
        case 4:
            if (f(l + (1 << 3))) l += 1 << 3;
        case 3:
            if (f(l + (1 << 2))) l += 1 << 2;
        case 2:
            if (f(l + (1 << 1))) l += 1 << 1;
        case 1:
            if (f(l + (1 << 0))) l += 1 << 0;
        default:
            break;
    }
    return l + 1;
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
        cout << find_first_false(
                    1, n / k,
                    [&](int m) {
                        const int inf = 1e9;
                        vector leftmost(k, vector(n + 1, inf));
                        for (int bit = 0; bit < k; ++bit) {
                            int prv = n;
                            for (int i = n - 1; i >= 0; --i) {
                                leftmost[bit][i] = leftmost[bit][i + 1];
                                if (s[i] != '?' and s[i] != 'a' + bit) prv = i;
                                if (prv >= i + m) leftmost[bit][i] = i;
                            }
                        }
                        vector<int> dp(1 << k, inf);
                        dp[0] = 0;
                        for (int mask = 0; mask < (1 << k); ++mask) {
                            if (dp[mask] >= n) continue;
                            for (int bit = 0; bit < k; ++bit)
                                if (!((mask >> bit) & 1))
                                    dp[mask ^ (1 << bit)] =
                                        min(dp[mask ^ (1 << bit)],
                                            leftmost[bit][dp[mask]] + m);
                        }
                        return dp[(1 << k) - 1] <= n;
                    }) -
                    1
             << '\n';
    }
}

