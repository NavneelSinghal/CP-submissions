 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 
 #define INF 1e9
 
 signed main() {
 
     ios_base::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);
 
     int c1, c2, c3, c4;
     cin >> c1 >> c2 >> c3 >> c4;
 
     int n, m;
     cin >> n >> m;
     vector<int> bus(n), tro(m);
     for(auto &x : bus) cin >> x;
     for(auto &x : tro) cin >> x;
 
     int ansb = 0;
     for(int i = 0; i < n; i++){
         ansb += min(c2, bus[i] * c1);
     }
     ansb = min(ansb, c3);
 
     int anst = 0;
     for(int i = 0; i < m; i++){
         anst += min(c2, tro[i] * c1);
     }
     anst = min(anst, c3);
 
     int ans = min(c4, ansb + anst);
 
     cout << ans << endl;
 
 }
