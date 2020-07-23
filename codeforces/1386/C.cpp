#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include <ext/rope>

using namespace __gnu_pbds;
//using namespace __gnu_cxx;
using namespace std;

//#define int long long
#define unordered_map gp_hash_table
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

struct custom_hash {
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

struct DSUOnSteroids {
    vector<int> e;
    vector<int> off;
    
    void init (int n) {
        e = vector<int>(n, -1);
        off = vector<int>(n);
    }
    
    pair<int, int> get (int x) {
        int answer = 0;
        while (e[x] >= 0) {
            answer ^= off[x];
            x = e[x];
        }
        return {x, answer};
    }

    vector<array<int, 4>> mod;
    
    int unite (int _x, int _y) {
        pair<int, int> x = get(_x), y = get(_y);
        
        if (x.first == y.first) {
            if (x.second == y.second) {
                debug(x, y, _x, _y);
                return 0;
            }
            mod.push_back({-1, -1, -1, -1});
            return 1;
        }

        if (e[x.first] > e[y.first]) 
            swap(x, y);
        
        mod.push_back({x.first, y.first, e[x.first], e[y.first]});
        
        e[x.first] += e[y.first];
        e[y.first] = x.first;
        off[y.first] = x.second ^ y.second ^ 1;
        
        return 1;
    }

    void rollback() {
    
        auto a = mod.back();
        mod.pop_back();
        
        if (a[0] != -1) {
            e[a[0]] = a[2];
            e[a[1]] = a[3];
        }
    
    }
};

DSUOnSteroids D;
int n, m, m1, q;
const int maxn = 2e5 + 5;
int best[maxn], u[maxn], v[maxn];

bool ad (int ind) {
    debug("AD", ind);
    if (ind == m1) return 1;
    return D.unite(u[ind], v[ind]);
}

void restore (int _sz) {
    while (D.mod.size() > _sz) {
        D.rollback();
        debug("ROLLBACK");
    }
}

void rec (int xl, int xr, int yl, int yr) {
    if (xl > xr) return;
    
    debug("DIVI", xl, xr, yl, yr, D.mod.size());
    assert(yl <= yr);

    int xm = (xl + xr) / 2;
    int res = -1;
    int _sz = D.mod.size();
    
    for (int i = xl; i < xm; ++i) {
        if (!ad(i)) {
            res = yr;
            assert(res == m1);
            break;
        }
    }
    
    int _sz1 = D.mod.size();
    if (res == -1) {
        int i = yr; 
        while (i > yl && ad(i)) i --; 
		res = i;
	}
    best[xm] = res;
    debug("SET", xm, best[xm]);
    if (best[xm] == m1) {
        for (int i = xm + 1; i <= xr; ++i) {
            best[i] = m1;
        }
    }
    
    else {
        restore(_sz1);
        if (!ad(xm)) {
            for (int i = xm + 1; i <= xr; ++i) {
                best[i] = m1;
            }
        }
        else {
            rec(xm + 1, xr, best[xm], yr);
        }
    }
    restore(_sz);
    for (int i = best[xm] + 1; i <= yr; ++i) {
        assert(ad(i));
    }
    rec(xl, xm - 1, yl, best[xm]);
    restore(_sz);
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    m1 = m + 1;
    debug(n, m, q);
    D.init(n + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> u[i] >> v[i];
    }
    
    rec(1, m, 1, m1);

    for (int i = 1; i <= m; ++i) {
        debug(i, best[i]);
    }

    for (int qq = 0; qq < q; ++qq) {
        int l, r;
        cin >> l >> r;
        cout << ((r < best[l]) ? "YES\n" : "NO\n");
    }

    return;
}

signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    //cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        solve();
    }

    return 0;
}


