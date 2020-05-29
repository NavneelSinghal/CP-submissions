 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 int sx(int b, int y){
 
 }
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
     int t;
     cin >> t;
     while(t--){
         int x1, y1, x2, y2;
         cin >> x1 >> y1 >> x2 >> y2;
         int d = min(x2 - x1, y2 - y1);
         int tot = x2 + y2 - x1 - y1;
         cout << d * (tot - d) + 1 << endl;
     }
 }
 
