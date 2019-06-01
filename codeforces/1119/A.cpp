#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (c[i] != c[n - 1]) {
      ans = max(ans, n - 1 - i);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (c[i] != c[0]) {
      ans = max(ans, i);
    }
  }
  cout << ans << "\n";
  return 0;
}