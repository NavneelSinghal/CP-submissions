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
    vi a(n);
    vi b(n);
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    int scorea = 0;
    int scoreb = 0;
    sort(all(a));
    sort(all(b));
    for(int i = 0; i < n; i++){
        //a's turn
        if(a.size() == 0){
            b.pop_back();
        }
        else if(b.size() == 0){
            scorea += a.back();
            a.pop_back();
        }
        else{
            if(a.back() > b.back()){
                scorea += a.back();
                a.pop_back();
            }
            else{
                b.pop_back();
            }
        }
        
        //b's turn
        if(b.size() == 0){
            a.pop_back();
        }
        else if(a.size() == 0){
            scoreb += b.back();
            b.pop_back();
        }
        else{
            if(b.back() > a.back()){
                scoreb += b.back();
                b.pop_back();
            }
            else{
                a.pop_back();
            }
        }
    }
    cout << scorea - scoreb << endl;
}
