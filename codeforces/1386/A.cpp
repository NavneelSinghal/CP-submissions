#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> v;
set<int> s;
bool querying;
int hi, lo;
int offset;

void query (int number) {
    s.insert(number);
    if (querying) cout << "? " << number << endl;
    v.push_back(number);
    bool b = false;
    if (querying) cin >> b;
    else if (abs(v[(int) v.size() - 2] - v.back()) >= n) b = 1;
    if (v.size() >= 2) {
        int diff = abs(v[(int) v.size() - 2] - v.back());
        if (b) {
            hi = min(hi, diff);
        }
        else lo = max(lo, diff + 1);
    }
}

pair<int, int> work() {
    v = {}, s = {};
    lo = 1, hi = n;
    query(offset);
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if ((lo & 1) == (hi & 1)) --mid;
        if (v.size() & 1) query(v.back() - mid);
        else query(v.back() + mid);
    }
    if (querying) cout << "= " << lo << endl;
    return {*s.begin(), *s.rbegin()}; 
}

void solve() {
    cin >> n;
    offset = 0;
    querying = false;
    pair<int, int> p = work();
    offset = 1 - p.first;
    querying = true;
    work();
    return;
}

signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        solve();
    }

    return 0;
}

