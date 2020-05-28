 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
 
     int t;
     cin >> t;
     while(t--){
         int n, m, k;
         cin >> n >> m >> k;
         if(m <= n/k){
             cout << m << endl;
         }
         else{
             m -= n/k;
             m = ceil(1.0 * m / (k-1));
             cout << n/k - m << endl;
         }
     }
 }
