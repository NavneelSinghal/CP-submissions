 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
 
     int n;
     cin >> n;
     vector<int> a(n);
     int ans = 0;
     for(int i = 0; i < n; i++) cin >> a[i];
     for(int m = -30; m <= 30; m++){
         //assume m is max
         int cur = 0;
         int best = -INF;
         for(int i = 0; i < n; i++){
             if(a[i] > m) continue;
             int j = i;
             cur = 0;
             while(j < n){
                 if(a[j] > m) break;
                 else{
                     cur += a[j];
                 }
                 best = max(best, cur);
                 if(cur < 0) cur = 0;
                 j++;
             }
             i = j;
         }
         ans = max(ans, best - m);
     }
     cout << ans << endl;
     return 0;
 }
