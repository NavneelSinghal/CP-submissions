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
         bool found = false;
         for(int i = 0; i < n-1; i++){
             if(a[i+1] - a[i] >= 2 || a[i] - a[i+1] >= 2){
                 cout << "YES\n" << i+1 << " " << i+2 << "\n";
                 found = true;
                 break;
             }
         }
         if(!found){
             cout << "NO\n";
         }
     }
 }
 
