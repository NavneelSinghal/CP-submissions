#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    int n = (int)s.size();
    const int A = 20;
    std::vector<int> dp(1 << A), popcnt(1 << A);

    for (int i = 1; i < (1 << A); ++i) popcnt[i] = popcnt[i >> 1] + (i & 1);

    for (int i = 0; i < n; ++i) {
        int mask = 0;
        for (int j = i; j < n; ++j) {
            auto c = s[j] - 'a';
            if ((mask >> c) & 1) break;
            mask |= 1 << c;
            dp[mask] = popcnt[mask];
        }
    }

    for (int mask = 0; mask < (1 << A); ++mask)
        for (int x = 0; x < A; ++x)
            if ((mask >> x) & 1)
                dp[mask] = std::max(dp[mask], dp[mask ^ (1 << x)]);

    int ans = 0;
    for (int mask = 0; mask < (1 << A); ++mask)
        if (dp[mask] == popcnt[mask])
            ans = std::max(ans, dp[mask] + dp[mask ^ ((1 << A) - 1)]);

    std::cout << ans << '\n';
}
