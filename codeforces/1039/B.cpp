#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __SIZEOF_INT128__
typedef __uint128_t uint128_t;
uint128_t mul_64_64(uint64_t a, uint64_t b) {
    return (uint128_t)a * b;
}
uint64_t get_lo_128(uint128_t a) {
    return (uint64_t)a;
}
uint64_t get_hi_128(uint128_t a) {
    return a >> 64u;
}
#else
typedef struct {
    uint64_t hi, lo;
} uint128_t;
uint128_t mul_64_64(uint64_t a, uint64_t b) {
    uint64_t a_hi = a >> 32u, a_lo = (uint32_t)a;
    uint64_t b_hi = b >> 32u, b_lo = (uint32_t)b;
    uint64_t cross = a_hi * b_lo + a_lo * b_hi;
    uint64_t hi = (a_hi * b_hi) | (cross >> 32u);
    uint64_t lo = (((uint64_t)((uint32_t)cross)) << 32u) | (a_lo * b_lo);
    return (uint128_t){hi, lo};
}
uint64_t get_lo_128(uint128_t a) {
    return a.lo;
}
uint64_t get_hi_128(uint128_t a) {
    return a.hi;
}
#endif

typedef struct {
    uint64_t state;
    uint64_t inc;
} pcg32_random_t;

uint32_t pcg32_random_r(pcg32_random_t* rng) {
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

pcg32_random_t rng;

uint32_t next_random_32() {
    return pcg32_random_r(&rng);
}

// perhaps use pcg64_random_r instead of this?
uint64_t next_random_64() {
    uint64_t high = next_random_32();
    uint64_t low = next_random_32();
    return (high << 32u) | low;
}

// [0, n)
uint32_t generate_random_n_32(uint32_t n) {
    uint64_t product = (uint64_t)next_random_32() * n;
    uint32_t lsb = (uint32_t)product;
    if (lsb < n) {
        uint32_t threshold = (-n) % n;
        while (lsb < threshold) {
            product = (uint64_t)next_random_32() * n;
            lsb = (uint32_t)product;
        }
    }
    return product >> 32;
}
uint64_t generate_random_n_64(uint64_t n) {
    uint128_t product = mul_64_64(next_random_64(), n);
    uint64_t lsb = get_lo_128(product);
    if (lsb < n) {
        uint64_t threshold = (-n) % n;
        while (lsb < threshold) {
            product = mul_64_64(next_random_64(), n);
            lsb = get_lo_128(product);
        }
    }
    return get_hi_128(product);
}

// [l, r]
uint32_t random_u32(uint32_t l, uint32_t r) {
    return l + generate_random_n_32(r - l + 1);
}
int32_t random_i32(int32_t l, int32_t r) {
    return l + generate_random_n_32(r - l + 1);
}
uint64_t random_u64(uint64_t l, uint64_t r) {
    return l + generate_random_n_64(r - l + 1);
}
int64_t random_i64(int64_t l, int64_t r) {
    return l + generate_random_n_64(r - l + 1);
}

void init_random() {
    char* c = (char*)malloc(sizeof(char));
    rng = (pcg32_random_t){(uint64_t)(c), 42};
    free(c);
}

typedef long long ll;

bool query(ll l, ll r) {
    printf("%lld %lld\n", l, r);
    fflush(stdout);
    char s[4];
    scanf("%s", s);
    return s[0] == 'Y';
}

int main() {
    init_random();
    ll n, k;
    scanf("%lld%lld", &n, &k);
    ll left = 1, right = n;
    while (true) {
        left = left - k > 1 ? left - k : 1;
        right = right + k < n ? right + k : n;
        if (right - left + 1 <= 60) {
            ll guess = left + (ll)generate_random_n_32(right - left + 1);
            if (query(guess, guess)) return 0;
        } else {
            ll mid = left + (right - left) / 2;
            if (query(left, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
    }
}
