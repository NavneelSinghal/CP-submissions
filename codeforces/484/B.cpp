#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int _a;
    set<int> s;
    int mx = 0;
    for(int i = 0; i < n; i++){
        cin >> _a;
        s.insert(_a);
        mx = max(mx, _a);
    }
    vector<int> a;
    for(int x : s){
        a.push_back(x);
    }
    n = a.size();
    int ret = 0;
    for(int i = 0; i < n; i++){
        int w = 2 + mx/a[i];
        for(int j = 2; j < w; j++){
            int ans = lower_bound(a.begin(), a.end(), j*a[i]) - a.begin();
            ans--;
            if(ans >= 0 && ans < n && a[ans] >= a[i]) ret = max(ret, (a[ans] % a[i]));
        }
    }
    cout << ret << endl;
    return 0;
}
