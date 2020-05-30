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
    for(auto &x : a) cin >> x;
    vector<int> left(n);
    vector<int> right(n);
    vector<int> leftel(n);
    vector<int> rightel(n);
    for(int i = 0; i < n-1; i++){
        leftel[i+1] = a[i];
    }
    for(int i = 1; i < n; i++){
        rightel[i-1] = a[i];
    }
    leftel[0] = -INF;
    rightel[n-1] = INF*2;
    int len = 0;
    for(int i = 0; i < n; i++){
        left[i] = len;
        if(leftel[i] < a[i]) len++;
        else len = 1;
    }
    len = 0;
    for(int i = n-1; i >= 0; i--){
        right[i] = len;
        if(rightel[i] > a[i]) len++;
        else len = 1;
    }
    int ans = 1 + *max_element(left.begin(), left.end());
    ans = max(ans, 1 + *max_element(right.begin(), right.end()));
    for(int i = 0; i < n; i++){
        if(leftel[i] < rightel[i] - 1){
            ans = max(left[i] + right[i] + 1, ans);
        }
    }
    cout << ans << endl;

}
