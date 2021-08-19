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
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        const auto get_next = [&](const string& a, int b) -> string {
            int curlen = (int)a.size();
            if (curlen * 9 < b) {
                curlen = (b + 8) / 9;
                string ans(curlen, '0');
                ans[0] = '1';
                --b;
                --curlen;
                while (b > 0) {
                    int increase = min(b, 9 - (ans[curlen] - '0'));
                    b -= increase;
                    ans[curlen] += increase;
                    --curlen;
                }
                return ans;
            } else {
                bool found = false;
                string best;
                for (int i = 0; i < curlen; ++i) {
                    if (a[i] == '9') continue;
                    string cur = a.substr(0, i);
                    cur += char(a[i] + 1);
                    cur += string(curlen - i - 1, '0');
                    int to_get = b;
                    for (auto c : cur) to_get -= c - '0';
                    if (to_get < 0) continue;
                    int pos = curlen - 1;
                    while (to_get > 0) {
                        int increase = min(to_get, 9 - (cur[pos] - '0'));
                        to_get -= increase;
                        cur[pos] += increase;
                        --pos;
                    }
                    if (!found)
                        best = cur, found = true;
                    else
                        best = min(best, cur);
                }
                if (found) return best;
                ++curlen;
                string ans(curlen, '0');
                ans[0] = '1';
                --b;
                --curlen;
                while (b > 0) {
                    int increase = min(b, 9 - (ans[curlen] - '0'));
                    b -= increase;
                    ans[curlen] += increase;
                    --curlen;
                }
                return ans;
            }
        };

        string ans = "0";
        for (int i = 0; i < n; ++i) {
            int b;
            cin >> b;
            ans = get_next(ans, b);
            cout << ans << '\n';
        }
    }
}

