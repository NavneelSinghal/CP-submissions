 #include <bits/stdc++.h>
 using namespace std;
 #define int long long
 #define rep(i, n) for(int i = 0; i < n; i++)
 
 signed main(){
     int t;
     cin >> t;
     while(t--){
         int a, b, c;
         cin >> a >> b >> c;
         int ans = 0;
         rep(i, (1 << 7)){
             int mask = i;
             int digits = 0;
             int t[3] = {0, 0, 0};
             rep(j, 7){
                 if(mask & (1 << j)){
                     digits++;
                     rep(k, 3){
                         if((j + 1) & (1 << k)){
                             t[k]++;
                         }
                     }
                 }
             }
             if(t[0] <= a && t[1] <= b && t[2] <= c){
                 ans = max(ans, digits);
             }
         }
         cout << ans << '\n';
     }
 }
