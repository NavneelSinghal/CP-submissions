#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, n) for(int i = 0; i < n; ++i)
#define repd(i, n) for(int i = n - 1; i >= 0; --i)
#define F first
#define S second
#define all(a) a.begin(), a.end()

vi prev_smaller(vi& arr){
    int n = arr.size();
    vi res(n);
    stack<pii> s;
    rep(i, n){
        while(!s.empty() && s.top().F >= arr[i]){
            s.pop();
        }
        if(!s.empty()){
            res[i] = s.top().S;
        }
        else{
            res[i] = -1;
        }
        s.push({arr[i], i});
    }
    return res;
}

vi next_smaller(vi& arr){
    int n = arr.size();
    vi res(n);
    stack<pii> s;
    repd(i, n){
        while(!s.empty() && s.top().F >= arr[i]){
            s.pop();
        }
        if(!s.empty()){
            res[i] = s.top().S;
        }
        else{
            res[i] = n;
        }
        s.push({arr[i], i});
    }
    return res;
}

signed main(){
    int n;
    cin >> n;
    vi m(n), l(n), r(n);
    rep(i, n) cin >> m[i];
    vi le = prev_smaller(m);
    vi ri = next_smaller(m);
    rep(i, n){
        if(le[i] == -1){
            l[i] = (i + 1) * m[i];
        }
        else{
            l[i] = l[le[i]] + (i - le[i]) * m[i];
        }
    }
    repd(i, n){
        if(ri[i] == n){
            r[i] = (n - i) * m[i];
        }
        else{
            r[i] = r[ri[i]] + (ri[i] - i) * m[i];
        }
    }
    int idx = -1;
    int ans = 0;
    rep(i, n){
        if(ans < l[i] + r[i] - m[i]){
            ans = l[i] + r[i] - m[i];
            idx = i;
        }
    }
    int prevht = m[idx];
    vi hts(n);
    hts[idx] = m[idx];
    repd(i, idx){
        hts[i] = min(m[i], hts[i + 1]);
    }
    for(int i = idx + 1; i < n; i++){
        hts[i] = min(m[i], hts[i - 1]);
    }
    rep(i, n){
        cout << hts[i] << ' ';
    }
    cout << endl;
    return 0;
    
}
