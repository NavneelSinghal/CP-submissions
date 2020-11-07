#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (name.size() == 0)
        return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    cout << setprecision(10) << fixed;
}

typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//order_of_key(k) - number of elements e such that func(e, k) returns true, where func is less or less_equal
//find_by_order(k) - kth element in the set counting from 0

const int INV_FACT = 14;
const int N = 1e6;
ordered_set pos;
long long a[N];
long long fact[INV_FACT];

void solve(int case_no) {

    int n, q;
    cin >> n >> q;
    
    iota(a, a + n, 1LL);

    fact[0] = 1;
    for (int i = 1; i < INV_FACT; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    long long x = 0, old_x;
    int lft = max(0, n - INV_FACT), iter = min(n, INV_FACT);

    while (q--) {
        
        int typ;
        cin >> typ;
        
        if (typ == 1) {

            int position = lft;
            for (int i = 1; i <= iter; ++i) pos.insert(i);
            old_x = x;
            int found_element;
            for (int i = iter - 1; ~i; --i) {
                long long w = x / fact[i];
                x %= fact[i];
                found_element = *pos.find_by_order(w);
                a[position++] = found_element + lft;
                pos.erase(found_element);
            }
            x = old_x;
            
            int l, r;
            cin >> l >> r;
            --l;
            
            assert(l >= 0 && l < r && r <= n);

            long long ans = 0;
            if (l >= lft) {
                for (int i = l; i < r; ++i) ans += a[i];
            } else if (r <= lft) {
                ans = (1LL * l + r + 1) * (r - l) / 2; 
            } else {
                ans = (1LL * l + lft + 1) * (lft - l) / 2;
                for (int i = lft; i < r; ++i) ans += a[i];
            }
            cout << ans << '\n';

        } else {

            int y;
            cin >> y;
            x += y;

        }
    }
}

signed main() {
    setIO();
    int t = 1;
    //cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        //cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}

