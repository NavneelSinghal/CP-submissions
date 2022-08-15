#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define MOD 998244353

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int binexp(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = mul(ans, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

int inv(int a) {
    return binexp(a, MOD - 2);
}

#define N 1000000

int fact[3 * N + 1], ifact[3 * N + 1];

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= 3 * N; ++i) fact[i] = mul(fact[i - 1], i);
    ifact[3 * N] = inv(fact[3 * N]);
    for (int i = 3 * N - 1; i >= 0; --i) ifact[i] = mul(ifact[i + 1], i + 1);
}

int C(int a, int b, int c, int d) {
    return mul(fact[a + b + c + d],
               mul(mul(ifact[a], ifact[b]), mul(ifact[c], ifact[d])));
}

int coeff(int a, int b, int c) {
    int x = a;
    if (b < x) x = b;
    if (c < x) x = c;
    int pw = 1, ans = 0;
    for (int i = 0; i <= x; ++i) {
        ans = add(ans, mul(pw, C(a - i, b - i, c - i, i)));
        pw = mul(pw, MOD - 2);
    }
    return ans;
}

int main() {
    init_fact();
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int ans = sub(
        add(add(coeff(a - 1, b, c), coeff(a, b - 1, c)), coeff(a, b, c - 1)),
        mul(3, coeff(a - 1, b - 1, c - 1)));
    printf("%d\n", ans);
}
