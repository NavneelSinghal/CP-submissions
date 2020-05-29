 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 int sx(int b, int y){
 
 }
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
     int t = 1;
     while(t--){
         int ans = 0;
         int n, x;
         cin >> n >> x;
         vector<int> a(2*n + 1), pre(2*n + 1), pre2(2*n + 1);
         for(int i = 1; i <= 2*n; i++){
             if(i <= n) cin >> a[i];
             else a[i] = a[i - n];
             pre[i] = pre[i-1] + a[i];
             pre2[i] = pre2[i-1] + a[i] * (a[i] + 1)/2;
         }
         int j = 0;
         for(int i = 1; i <= 2*n; i++){
             while(pre[i] - pre[j] > x) j++;
             if(i > n){
                 int val = pre2[i] - pre2[j];
                 int rem = x - (pre[i] - pre[j]);
                 val += (a[j] - rem + 1 + a[j]) * rem / 2;
                 ans = max(ans, val);
             }
         }
         cout << ans << endl;
     }
 }
