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
         int n;
         cin >> n;
         vector<int> a(n);
         for(auto &x : a) cin >> x;
         sort(a.begin(), a.end());
         int ans = 1;
         for(int i = n-1; i >= 0; i--){
             if(a[i] <= i + 1){
                 ans += i+1;
                 break;
             }
         }
         cout << ans << endl;
     }
 }
 
