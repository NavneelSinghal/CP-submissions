 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
 
     int n, k;
     cin >> n >> k;
 
     k = min(k, n/2);
 
     int ans = 0;
 
     for(int i = 0; i < k; i++){
         ans += 2*n - 3 - 4*i;
     }
 
     cout << ans << endl;
 
 }
