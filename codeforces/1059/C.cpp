#include <bits/stdc++.h>
using namespace std;

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    
    function<vector<int>(int)> solve = [&] (int n) {
        if (n == 1) return vector<int> {1};
        if (n == 2) return vector<int> {1, 2};
        if (n == 3) return vector<int> {1, 1, 3};
        vector<int> v = solve(n >> 1);
        int remaining = n - (n >> 1);
        vector<int> answer(remaining, 1);
        for (auto &&x : v) answer.push_back(x << 1);
        return answer;
    };

    auto a = solve(n);
    for (auto x : a) cout << x << ' ';
    cout << '\n';

    return 0;
}
