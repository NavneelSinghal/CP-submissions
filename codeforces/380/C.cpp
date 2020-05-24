#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> b, o, c;
string s;

void build(int v, int tl, int tr){
    if(tl == tr){
        if(s[tl] == '('){
            o[v] = 1;
        }
        else{
            c[v] = 1;
        }
    }
    else{
        int tm = (tl + tr)/2;
        build(2*v+1, tl, tm);
        build(2*v+2, tm+1, tr);
        int nb = min(o[2*v+1], c[2*v+2]);
        b[v] = b[2*v+1] + b[2*v+2] + nb;
        o[v] = o[2*v+1] + o[2*v+2] - nb;
        c[v] = c[2*v+1] + c[2*v+2] - nb;
    }
}

tuple<int, int, int> query(int v, int tl, int tr, int l, int r){
    if(l > r){
        return make_tuple(0, 0, 0);
    }
    if(l == tl && r == tr){
        return make_tuple(b[v], o[v], c[v]);
    }
    int tm = (tl + tr)/2;
    tuple<int, int, int> t1 = query(v*2+1, tl, tm, l, min(r, tm)), t2 = query(v*2+2, tm+1, tr, max(l, tm+1), r);
    int b1, o1, c1, b2, o2, c2, bn, on, cn;
    tie(b1, o1, c1) = t1;
    tie(b2, o2, c2) = t2;
    int nb = min(o1, c2);
    bn = b1 + b2 + nb;
    on = o1 + o2 - nb;
    cn = c1 + c2 - nb;
    return make_tuple(bn, on, cn);
}

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> s;
    int n = s.size();
    b.resize(4*n);
    o.resize(4*n);
    c.resize(4*n);

    build(0, 0, n-1);

    int m, l, r;
    cin >> m;
    while(m--){
        cin >> l >> r;
        --l, --r;
        int ans = 2*get<0>(query(0, 0, n-1, l, r));
        cout << ans << "\n";
    }
}

