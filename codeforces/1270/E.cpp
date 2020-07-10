#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;

#define int long long
#define double long double
#define Int signed
#define vi vector<int>
#define vI vector<Int>
#define vvi vector<vi>
#define vvI vector<vI>
#define vd vector<double>
#define vvd vector<vd>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mii map<int, int>
#define unordered_map gp_hash_table

#define OVERLOADED_MACRO(M, ...) _OVR(M, _COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)
#define _OVR(macroName, number_of_args)   _OVR_EXPAND(macroName, number_of_args)
#define _OVR_EXPAND(macroName, number_of_args)    macroName##number_of_args

#define _COUNT_ARGS(...)  _ARG_PATTERN_MATCH(__VA_ARGS__, 9,8,7,6,5,4,3,2,1)
#define _ARG_PATTERN_MATCH(_1,_2,_3,_4,_5,_6,_7,_8,_9, N, ...)   N

#define rep(...) OVERLOADED_MACRO(rep, __VA_ARGS__)
#define repd(...) OVERLOADED_MACRO(repd, __VA_ARGS__)

#define rep3(i, a, b) for (int i = a; i < b; ++i)
#define rep2(i, n) rep3(i, 0, n)
#define repd3(i, a, b) for(int i = b - 1; i >= a; --i)
#define repd2(i, n) repd3(i, 0, n)
#define rep4(i, a, b, c) for(int i = a; i < b; i += c)

#define F first
#define S second

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

#define bitcount __builtin_popcountll
//for trailing 1s, do trailing0(n + 1)
#define leading0 __builtin_clzll
#define trailing0 __builtin_ctzll
#define isodd(n) (n & 1)
#define iseven(n) (!(n & 1))

#define sz(v) ((int) v.size())
#define del_rep(v) sort(all(v)); v.erase(unique(all(v)), v.end());
#define checkbit(n, b) ((n >> b) & 1)

#ifdef DEBUG
#define debug(args...) {\
    std::string _s = #args;\
    replace(_s.begin(), _s.end(), ',', ' ');\
    std::stringstream _ss(_s);\
    std::istream_iterator <std::string> _it(_ss);\
    err(_it, args);\
}
#define print_container(v) {\
    bool first = true; os << "[";\
    for (auto x : v) {\
        if (!first) os << ", "; os << x; first = false;\
    }\
    return os << "]";\
}
void err (std::istream_iterator <std::string> it) {}
template <typename T, typename... Args>
void err (std::istream_iterator <std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}
template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::vector<T>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::set<T>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::map<T1, T2>& v) { print_container(v); }
template <typename T1, typename T2, class C> inline std::ostream &operator << (std::ostream & os, const unordered_map<T1, T2, C>& v) { print_container(v); }
template <typename T, class C> inline std::ostream &operator << (std::ostream & os, const unordered_set<T, C>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::multimap<T1, T2>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::multiset<T>& v) { print_container(v); }
#else
#define debug(args...) 0
#endif

//order_of_key(k) - number of elements e such that func(e, k) returns true, where func is less or less_equal
//find_by_order(k) - kth element in the set counting from 0
//
typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

const int INF = 1e9;
const int LINF = INF * INF;
const double EPS = 1e-9;
const double PI = acosl(-1);
const int mod = 1e9 + 7;
const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

//older machines
//use only for non-negative u, v
int32_t gcd (int32_t u, int32_t v) {
    int32_t shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            swap(u, v);
        }
        v -= u;
    } while (v);
    return u << shift;
}

//use only for non-negative u, v
long long gcd (long long u, long long v) {
    int32_t shift;
    if (u == 0 || v == 0) return u + v;
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) {
            swap(u, v);
        }
        v -= u;
    } while (v);
    return u << shift;
}

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

int n;
vpii v;
vvi a(4);

bool onlyone() {
    int tot = 0;
    rep (i, 4) {
        tot += (a[i].size() > 0);
    }
    return tot == 1;
}

void reassign(int c) {
    rep (i, 4) vi().swap(a[i]);
    int dy = c & 1;
    int dx = (c >> 1) & 1;
    int i = 0;
    for (auto &[x, y] : v) {
        y = (y - dy) / 2;
        x = (x - dx) / 2;
        a[((x & 1) << 1) | (y & 1)].pb(i);
        ++i;
    }
}

void solve() {
    cin >> n;
    rep (i, n) {
        int x, y;
        cin >> x >> y;
        v.eb(x, y);
        a[((x & 1) << 1) | (y & 1)].pb(i);
    }
    while (onlyone()) {
        debug(a);
        debug(v);
        rep (i, 4) {
            if (a[i].size()) {
                reassign(i);
                break;
            }
        }
    }
    //now at least two are non-empty
    int a0 = a[0].size();
    int a1 = a[1].size();
    int a2 = a[2].size();
    int a3 = a[3].size();
    
    if (!a0 && a1 && a2 && !a3) {
        cout << a1 << endl;
        for (auto i : a[1]) {
            cout << i + 1 << " ";
        }
        cout << endl;
        return;
    }

    if (a0 && !a1 && !a2 && a3) {
        cout << a0 << endl;
        for (auto i : a[0]) {
            cout << i + 1 << " ";
        }
        cout << endl;
        return;
    }

    cout << a0 + a3 << endl;
    for (auto i : a[0]) cout << i + 1 << " ";
    for (auto i : a[3]) cout << i + 1 << " ";
    cout << endl;
    return;
}

signed main(){
    //IOinit();
    fastio;
    //cout << setprecision(6) << fixed;
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    //_flush_output();
    return 0;
}

