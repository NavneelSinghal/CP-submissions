#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <assert.h>
#include <stdio.h>

#define ll long long
#define ull unsigned long long
#define N 200000
#define S 100

char buf[N * 22];
char buf2[N * 22];
char* bufptr = &*buf;
char* bufptr2 = &*buf2;

// assumes "x y z"
ull read_non_negative() {
    ++bufptr;
    ull ans = 0;
    while (*bufptr >= '0') ans = ans * 10 + *(bufptr++) - '0';
    return ans;
}

void print_char(char x) {
    *(bufptr2++) = x;
}

// print only till 999999
void print(unsigned x) {
    assert(x < 1000000);
    // 1, 2, 3, 4, 5, 6
    if (x < 1000) {
        if (x < 10) {
            print_char(x + 48);
        } else if (x < 100) {
            print_char(x / 10 + 48);
            print_char(x % 10 + 48);
        } else {
            print_char(x / 100 + 48);
            print_char((x / 10) % 10 + 48);
            print_char(x % 10 + 48);
        }
    } else {
        if (x < 10000) {
            print_char(x / 1000 + 48);
            print_char((x / 100) % 10 + 48);
            print_char((x / 10) % 10 + 48);
            print_char(x % 10 + 48);
        } else if (x < 100000) {
            print_char(x / 10000 + 48);
            print_char((x / 1000) % 10 + 48);
            print_char((x / 100) % 10 + 48);
            print_char((x / 10) % 10 + 48);
            print_char(x % 10 + 48);
        } else {
            print_char(x / 100000 + 48);
            print_char((x / 10000) % 10 + 48);
            print_char((x / 1000) % 10 + 48);
            print_char((x / 100) % 10 + 48);
            print_char((x / 10) % 10 + 48);
            print_char(x % 10 + 48);
        }
    }
}

ll abs_(ll a) {
    return a < 0 ? -a : a;
}

ull gcd(ull a, ull b) {
    if (!a || !b) return a | b;
    int i = __builtin_ctzll(a);
    int j = __builtin_ctzll(b);
    a >>= i;
    b >>= j;
    int k = i < j ? i : j;
    while (1) {
        if (a > b) {
            ull t = a;
            a = b;
            b = t;
        }
        b -= a;
        if (b == 0) return a << k;
        b >>= __builtin_ctzll(b);
    }
}

ll a[N];
ull distinct[S];
int index[S];

int main() {
    fread(buf + 1, 1, sizeof(buf) - 1, stdin);
    int t = (int)read_non_negative();
    while (t--) {
        int n = (int)read_non_negative();
        for (int i = 0; i < n; ++i) a[i] = read_non_negative();
        if (n == 1) {
            print(1);
            print_char('\n');
            continue;
        }
        --n;
        for (int i = 0; i < n; ++i) a[i] = abs_(a[i] - a[i + 1]);
        int ans = 0, ptr = 0;
        for (int i = 0; i < n; ++i) {
            distinct[ptr] = a[i];
            index[ptr] = i;
            for (int j = ptr - 1; j >= 0; --j)
                distinct[j] = gcd(distinct[j], distinct[j + 1]);
            int newptr = 1;
            for (int j = 1; j <= ptr; ++j) {
                if (distinct[j] != distinct[j - 1]) {
                    distinct[newptr] = distinct[j];
                    index[newptr] = index[j];
                    ++newptr;
                }
            }
            ptr = newptr;
            if (distinct[0] != 1) {
                if (ans < i + 1) ans = i + 1;
            } else if (newptr > 1) {
                if (ans < i + 1 - index[1]) ans = i + 1 - index[1];
            }
        }
        print(ans + 1);
        print_char('\n');
    }
    fwrite(buf2, 1, bufptr2 - buf2, stdout);
}
