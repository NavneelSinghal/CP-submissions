#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using namespace std;

using ll = int64_t;
using ld = long double;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        ll n, ax, bx, ay, by;
        cin >> n >> ax >> bx >> ay >> by;
        if (bx == by) {
            cout << (ax == ay) * n << '\n';
            continue;
        }
        if (bx > by) {
            swap(bx, by);
            swap(ax, ay);
        }
        ll diff = ay - ax;
        auto floor_div = [](ll x, ll y) {
            return x / y;
        };
        auto ceil_div = [](ll x, ll y) {
            return (x + y - 1) / y;
        };
        auto sum = [&floor_div](ll a, ll b, ll n) {
            ll ans = n * a;
            // [0, n)
            // [0, b), ..., [floor(n/b)*b - b, floor(n/b)*b), [floor(n/b)*b, n)
            //  0            floor(n/b) - 1                    floor(n/b)
            ll x = floor_div(n, b);
            ans += b * (x * (x - 1) / 2);
            ans += x * (n - x * b);
            return ans;
        };
        auto ans_small = [&] {
            ll n_min = floor_div((diff - 1) * bx * by, by - bx);
            ll n_max = ceil_div(diff * bx * by, by - bx);
            debug(n_min, n_max);
            // [n_min, n_max)
            assert(n_min <= n_max);
            n_max = min(n_max, n + 1);
            n_min = max(n_min, ll(1));
            debug(n_min, n_max);
            if (n_min >= n_max) return ll(0);
            ll ans = n_max - n_min +
                     (sum(ax, bx, n_max) - sum(ax, bx, n_min) -
                      sum(ay, by, n_max) + sum(ay, by, n_min));
            debug(ans);
            return ans;
        };
        auto ans_large = [&] {
            ll n_min = floor_div(diff * bx * by, by - bx);
            ll n_max = ceil_div((diff + 1) * bx * by, by - bx);
            debug(n_min, n_max);
            // [n_min, n_max)
            assert(n_min <= n_max);
            n_max = min(n_max, n + 1);
            n_min = max(n_min, ll(1));
            debug(n_min, n_max);
            if (n_min >= n_max) return ll(0);
            ll ans = n_max - n_min +
                     (-sum(ax, bx, n_max) + sum(ax, bx, n_min) +
                      sum(ay, by, n_max) - sum(ay, by, n_min));
            debug(ans);
            return ans;
        };
        ll ans = 0;
        if (diff >= 1) {
            ans = ans_small() + ans_large();
            ll collision = floor_div(diff * bx * by, by - bx);
            debug(collision);
            if (collision <= n && collision >= 1 &&
                collision * (by - bx) != diff * bx * by) {
                if (ax + floor_div(collision, bx) ==
                    ay + floor_div(collision, by)) {
                    ans--;
                }
            }
        } else if (diff == 0) {
            ans = ans_large();
        } else {
            ans = 0;
        }
        cout << ans << '\n';
#ifdef DEBUG
        auto brute = [](ll ax, ll bx, ll ay, ll by, ll n) {
            ll ans = 0;
            for (int i = 1; i <= n; ++i) {
                ll val_x = ax + i / bx;
                ll val_y = ay + i / by;
                if (val_x == val_y) ans++;
            }
            return ans;
        };
        if (ans != brute(ax, bx, ay, by, n)) {
            debug(ax, bx, ay, by, n);
            debug("actual:", brute(ax, bx, ay, by, n));
            debug("computed:", ans);
            return 0;
        }
#endif
    }
}
