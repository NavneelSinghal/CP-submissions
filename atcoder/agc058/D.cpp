#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <stdio.h>

#define MOD 998244353

unsigned add(unsigned a, unsigned b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

unsigned sub(unsigned a, unsigned b) {
    if (a < b) return a + MOD - b;
    return a - b;
}

unsigned mul(unsigned a, unsigned b) {
    return 1ULL * a * b % MOD;
}

unsigned binexp(unsigned a, unsigned n) {
    unsigned ans = 1;
    while (n) {
        if (n & 1) ans = mul(ans, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

unsigned inv(unsigned a) {
    return binexp(a, MOD - 2);
}

#define N 1000000

unsigned fact[3 * N + 1], ifact[3 * N + 1], pw[N + 1];

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= 3 * N; ++i) fact[i] = mul(fact[i - 1], i);
    ifact[3 * N] = inv(fact[3 * N]);
    for (int i = 3 * N - 1; i >= 0; --i) ifact[i] = mul(ifact[i + 1], i + 1);
    pw[0] = 1;
    for (int i = 1; i <= N; ++i) pw[i] = mul(pw[i - 1], MOD - 2);
}

unsigned C(unsigned a, unsigned b, unsigned c, unsigned d) {
    return mul(fact[a + b + c + d],
               mul(mul(ifact[a], ifact[b]), mul(ifact[c], ifact[d])));
}

unsigned coeff(unsigned a, unsigned b, unsigned c) {
    unsigned x = a;
    if (b < x) x = b;
    if (c < x) x = c;
    unsigned ans = 0;
    for (unsigned i = 0; i <= x; ++i)
        ans = add(ans, mul(pw[i], C(a - i, b - i, c - i, i)));
    return ans;
}

int main() {
    init_fact();
    unsigned a, b, c;
    scanf("%u%u%u", &a, &b, &c);
    unsigned ans = sub(
        add(add(coeff(a - 1, b, c), coeff(a, b - 1, c)), coeff(a, b, c - 1)),
        mul(3, coeff(a - 1, b - 1, c - 1)));
    printf("%u\n", ans);
}
