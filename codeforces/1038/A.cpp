 #include <bits/stdc++.h>
 using namespace std;
 
 #define int long long
 #define vi vector<int>
 #define vvi vector<vector<int>>
 #define pii pair<int, int>
 #define vpii vector<pair<int, int>> 
 #define rep(i, n) for(int i = 0; i < n; i++)
 #define repd(i, n) for(int i = n-1; i >= 0; i--)
 #define F first
 #define S second
 #define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 #define pb push_back
 #define mp make_pair
 #define eb emplace_back
 #define all(v) v.begin(),v.end()
 #define INF 1e9
 
 
 signed main() {
     fastio;
     int n;
     cin >> n;
     int k;
     cin >> k;
     string s;
     cin >> s;
     vi freq(k);
     rep(i, n){
         freq[s[i] - 'A'] ++;
     }
     cout << k * (*min_element(all(freq))) << endl;
 }
