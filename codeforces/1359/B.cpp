 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 char c[1005][1005];
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
 
     int t;
     cin >> t;
     while(t--){
         int n, m, x, y;
         cin >> n >> m >> x >> y;
         y = min(y, 2 * x);
         int ans = 0;
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= m; j++) {
                 cin >> c[i][j];
                 if (c[i][j] == '.') {
                     if (j != 1 && c[i][j - 1] == '.' && c[i][j] == '.') {
                         c[i][j] = '*';
                         c[i][j - 1] = '*';
                         ans += y;
                     }
                 }
             }
         }
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= m; j++) {
                 if (c[i][j] == '.') ans += x;
             }
         }
         cout << ans << '\n';
     }
 }
