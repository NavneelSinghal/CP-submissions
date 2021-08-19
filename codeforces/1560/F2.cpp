// original: https://codeforces.com/contest/1560/submission/126422178

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include "bits/stdc++.h"
#define ll long long
using namespace std;

string s;
int k, x;
vector<int> digit;
int pr[10];
int dp[11][1025][2];

int memo(int i, int mask, int large) {
    if (i == x) return (__builtin_popcount(mask) <= k);
    int& ans = dp[i][mask][large];
    if (ans != -1) return ans;
    ans = 0;
    if (large == 0) {
        for (int j = digit[i]; j <= 9; j++) {
            int y = 1 << j;
            ans |= memo(i + 1, mask | y, (j > digit[i]));
            if (ans) {
                pr[i] = j;
                break;
            }
        }
    } else {
        for (int j = 0; j <= 9; j++) {
            int y = 1 << j;
            ans |= memo(i + 1, mask | y, 1);
            if (ans) {
                pr[i] = j;
                break;
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        digit.clear();
        cin >> s >> k;
        for (char c : s) digit.push_back(c - '0');
        x = (int)digit.size();
        int n = (int)digit.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= 1024; j++) dp[i][j][0] = dp[i][j][1] = -1;
        int can = memo(0, 0, 0);
        ignore = can;
        for (int i = 0; i < x; i++) cout << pr[i];
        cout << '\n';
    }
}

