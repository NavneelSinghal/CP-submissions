#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

//smaller names
#define int long long
#define double long double
#define Int signed
#define vi vector<int>
#define vvi vector<vi>
#define vd vector<double>
#define vvd vector<vd>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mii map<int, int>
#define unordered_map gp_hash_table

#define rep(i, n) for(int i = 0; i < n; i++)
#define rep2(i, a, b) for(int i = a; i < b; i++)
#define repd2(i, a, b) for(int i = b - 1; i >= a; i--)
#define repd(i, n) for(int i = n-1; i >= 0; i--)

#define F first
#define S second

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

const int INF = 1e9;
const double EPS = 1e-9;
const double PI = acosl(-1);

//order_of_key(k) - number of elements e such that func(e, k) returns true, where func is less or less_equal
//find_by_order(k) - kth element in the set counting from 0

typedef tree <
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> 
ordered_set;

typedef tree <
    int,
    null_type,
    less_equal<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
>
ordered_multiset;

const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

//fast exponentiation

template <typename T>
T power (T a, int n = 1, T id = 1) {
    T ans = id;
    while(n) {
        if(n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

//custom hash

struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int sumdigs (int n) {
    int ans = 0;
    while (n) {
        ans += n % 10;
        n /= 10;
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vi t(n), a(n), b(n);
    rep(i, n) cin >> t[i] >> a[i] >> b[i];
    int suma = 0, sumb = 0;
    rep(i, n) suma += a[i], sumb += b[i];
    if(suma < k || sumb < k) {
        cout << -1 << "\n";
        return;
    }
    vi typ[3];
    rep(i, n) {
        if(a[i] && b[i]) 
            typ[0].pb(t[i]);
        else if (a[i]) 
            typ[1].pb(t[i]);
        else if (b[i])
            typ[2].pb(t[i]);
    }
    rep(i, 3) sort(all(typ[i]));
    vi pre0(1 + typ[0].size()), pre1(1 + typ[1].size()), pre2(1 + typ[2].size());
    int p1 = 0, p2 = 0, p0 = 0;
    rep(i, (int) typ[1].size()) {
        p1 += typ[1][i];
        pre1[i+1] = p1;
    }
    rep(i, (int) typ[2].size()) {
        p2 += typ[2][i];
        pre2[i+1] = p2;
    }
    rep(i, (int) typ[0].size()) {
        p0 += typ[0][i];
        pre0[i+1] = p0;
    }
    int ans = 1e18;
    for (int i = 0; i <= min(k, (int) typ[0].size()); i++) {
        int cost = 0;
        int num = 0;
        cost += pre0[i];
        num += i;
        if (typ[1].size() + i < k) continue;
        if (typ[2].size() + i < k) continue;
        cost += pre1[k - i] + pre2[k - i];
        num += 2*(k-i);
        ans = min(ans, cost);
    }
    if(ans == 1e18) cout << -1 << "\n";
    else cout << ans << "\n";
}

signed main(){
    fastio;
    cout << setprecision(6) << fixed;
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}
