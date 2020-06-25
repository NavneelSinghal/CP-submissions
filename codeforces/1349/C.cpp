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

template <int MOD=998'244'353>
struct Modular {
    int value;
    static const int MOD_value = MOD;

    Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
    Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}

    Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
    Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
    Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}

    friend Modular mexp(Modular a, long long e) {
        Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
        return res;
    }
    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

    Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
    friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
    friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
};

using mint = Modular<mod>;

vpii dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m, t;

bool check(int i, int j) {
    return i>=0 && i<n && j>=0 && j<m;
}

void solve() {
    cin >> n >> m >> t;
    vector<string> a(n);
    rep(i, n) cin >> a[i];
    vvi dist(n, vi(m, 2*INF*INF));
    queue<pii> q;
    vvi good(n, vi(m));
    rep(i, n) rep(j, m) {
        for(auto x : dirs) {
            if(check(i+x.F, j+x.S) && a[i][j] == a[i+x.F][j+x.S]) {
                good[i][j] = 1;
                q.push({i, j});
                dist[i][j] = 0;
                break;
            }
        }
    }
    while(!q.empty()) {
        pii p = q.front();
        q.pop();
        int i = p.F, j = p.S;
        for(auto x : dirs) {
            if(check(i+x.F, j+x.S) && dist[i+x.F][j+x.S] == INF*INF*2) {
                dist[i+x.F][j+x.S] = dist[i][j] + 1;
                q.push({i+x.F, j+x.S});
            }
        }
    }
    while(t--) {
        int i, j;
        cin >> i >> j;
        --i, --j;
        int p;
        cin >> p;
        int ans = a[i][j] - '0';
        if(p >= dist[i][j]) cout << ((ans ^ (p - dist[i][j])) & 1) << "\n";
        else cout << ans << "\n";
    }

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
