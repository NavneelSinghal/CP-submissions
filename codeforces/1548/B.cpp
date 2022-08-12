#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define ll long long
#define ull unsigned long long
#define N 200000
#define S 100

char buf[N * 30];
char* bufptr = &*buf;
char buf2[N * 30];
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

ll abs(ll a) {
    return a < 0 ? -a : a;
}

ll gcd(ll a, ll b) {
    if (!a || !b) return a | b;
    int c = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    b >>= __builtin_ctzll(b);
    if (a < b) {
        ll t = a;
        a = b;
        b = t;
    }
    while (b) {
        do {
            a -= b;
            a >>= __builtin_ctzll(a);
        } while (a >= b);
        ll t = a;
        a = b;
        b = t;
    }
    return a << c;
}

ll a[N], distinct[S];
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
        for (int i = 0; i < n; ++i) a[i] = abs(a[i] - a[i + 1]);
        int ans = 0, ptr = 0;
        for (int i = 0; i < n; ++i) {
            distinct[ptr] = a[i];
            index[ptr] = i;
            for (int j = ptr - 1; j >= 0; --j)
                distinct[j] = gcd(distinct[j], distinct[j + 1]);
            int newptr = 0;
            for (int j = 0; j <= ptr; ++j) {
                if (j == 0 || distinct[j] != distinct[j - 1]) {
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

