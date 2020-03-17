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

void prev_smaller(vi& arr, vi& res){
    int n = arr.size();
    stack<pii> s;
    rep(i, n){
        while(!s.empty() && s.top().F >= arr[i]) s.pop();
        if(!s.empty()) res[i] = s.top().S;
        else res[i] = -1;
        s.push({arr[i], i});
    }
}

void next_smaller(vi& arr, vi& res){
    int n = arr.size();
    stack<pii> s;
    repd(i, n){
        while(!s.empty() && s.top().F >= arr[i]) s.pop();
        if(!s.empty()) res[i] = s.top().S;
        else res[i] = n;
        s.push({arr[i], i});
    }
}

signed main(){
    int n;
    cin >> n;
    vi m(n), l(n), r(n), le(n);
    rep(i, n) cin >> m[i];
    prev_smaller(m, le);
    rep(i, n){
        int lei = le[i];
        if(lei == -1) l[i] = (i + 1) * m[i];
        else l[i] = l[lei] + (i - lei) * m[i];
    }
    next_smaller(m, le);
    repd(i, n){
        int rii = le[i];
        if(rii == n) r[i] = (n - i) * m[i];
        else r[i] = r[rii] + (rii - i) * m[i];
    }
    int idx = -1;
    int ans = 0;
    rep(i, n){
        int wt = l[i] + r[i] - m[i];
        if(ans < wt){
            ans = wt;
            idx = i;
        }
    }
    vi hts(n);
    hts[idx] = m[idx];
    repd(i, idx) hts[i] = min(m[i], hts[i + 1]);
    for(int i = idx + 1; i < n; ++i) hts[i] = min(m[i], hts[i - 1]);
    rep(i, n) cout << hts[i] << ' ';
    cout << '\n';
    return 0;
}
