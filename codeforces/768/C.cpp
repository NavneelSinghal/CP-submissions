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
#define vvi vector<vi>
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

#define F first
#define S second

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(),v.end()

#define bitcount __builtin_popcountll
#define gcd __gcd
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
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os, const std::vector<T>& v) {
    print_container(v);
}
template<typename T>
inline std::ostream &operator << (std::ostream & os, const std::set<T>& v) {
    print_container(v);
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os, const std::map<T1, T2>& v) {
    print_container(v);
}
template<typename T1, typename T2, class C>
inline std::ostream &operator << (std::ostream & os, const unordered_map<T1, T2, C>& v) {
    print_container(v);
}
template<typename T, class C>
inline std::ostream &operator << (std::ostream & os, const unordered_set<T, C>& v) {
    print_container(v);
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os, const std::multimap<T1, T2>& v) {
    print_container(v);
}
template<typename T>
inline std::ostream &operator << (std::ostream & os, const std::multiset<T>& v) {
    print_container(v);
}
#else
#define debug(args...) 0
#endif

//order_of_key(k) - number of elements e such that func(e, k) returns true, where func is less or less_equal
//find_by_order(k) - kth element in the set counting from 0
//
typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

const int INF = 1e9;
const double EPS = 1e-9;
const double PI = acosl(-1);
const int mod = 1e9 + 7;
const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

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

struct pair_hash {
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
    size_t operator()(pair<int, int> p) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(p.first * 31 + p.second + FIXED_RANDOM);
    }
};

vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 128;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    //base case : length = 1, so sort by counting sort
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) ++classes;
        c[p[i]] = classes - 1;
    }
    //inductive case, sort by radix sort on pairs (in fact you only need to sort by first elements now)
    vector<int> p_new(n), c_new(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            p_new[i] = p[i] - (1 << h);
            if (p_new[i] < 0) p_new[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[p_new[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[p_new[i]]]] = p_new[i];
        c_new[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            c_new[p[i]] = classes - 1;
        }
        c.swap(c_new);
    }
    return p;
}
vector<int> suffix_array_construct (string s) {
    s += "$";
    //what about s += " "; ?
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    //sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    vi freq(1024);
    rep(i, n) {
        int w;
        cin >> w;
        freq[w]++;
    }
    rep(_, k) {
        vi upd(1024);
        int state = 1; //on
        rep(i, 1024) {
            upd[i ^ x] += (freq[i] + state) / 2;
            upd[i] += freq[i] - (freq[i] + state) / 2;
            state = (state + freq[i]) & 1;
        }
        freq.swap(upd);
    }
    bool fmin = false;
    int mx = 0, mn = 0;
    rep(i, 1024) {
        if(!fmin && freq[i] > 0) {
            mn = i;
            fmin = true;
        }
        if(freq[i] > 0) mx = i;
    }
    cout << mx << " " << mn << endl;
}

signed main(){
    fastio;
    cout << setprecision(6) << fixed;
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
