// --------------------------------------------------<TEMPLATE>--------------------------------------------------
// --------------------<optimizations>--------------------
#pragma GCC optimize("O3")
//(UNCOMMENT WHEN HAVING LOTS OF RECURSIONS)\
#pragma comment(linker, "/stack:200000000")
//(UNCOMMENT WHEN TRYING TO BRUTEFORCE WITH A LOT OF LOOPS)\
#pragma GCC optimize("unroll-loops")
 
// -------------------</optimizations>--------------------
 
// ---------------<Headers and namespaces>----------------
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
// ---------------</Headers and namespaces>---------------
 
// -----------------<Defines and typedefs>----------------
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth largest element.(0-based)
 
typedef long long ll;
typedef long double LD;
#define int ll
#define double LD
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define ITR :: iterator it
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define TR(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define sqr(x) ((x)*(x))
 
// -----<SCANF>-----
#define sfi(x) scanf("%d",&x);
#define sfi2(x,y) scanf("%d%d",&x,&y);
#define sfi3(x,y,z) scanf("%d%d%d",&x,&y,&z);
 
#define sfl(x) scanf("%lld",&x);
#define sfl2(x,y) scanf("%lld%lld",&x,&y);
#define sfl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
 
#define sfs(x) scanf("%s",&x);
#define sfs2(x,y) scanf("%s%s",&x,&y);
#define sfs3(x,y,z) scanf("%s%s%s",&x,&y,&z);
// ----</SCANF>-----
 
// ----<PRINTF>-----
#define pfi(x) printf("%d\n",x);
#define pfi2(x,y) printf("%d %d\n",x,y);
#define pfi3(x,y,z) printf("%d %d %d\n",x,y,z);
 
#define pfl(x) printf("%lld\n",x);
#define pfl2(x,y) printf("%lld %lld\n",x,y);
#define pfl3(x,y,z) printf("%lld %lld %lld\n",x,y,z);
 
#define pfs(x) printf("%s\n",x);
#define pfs2(x,y) printf("%s %s\n",x,y);
#define pfs3(x,y,z) printf("%s %s %s\n",x,y,z);
// ----</PRINTF>----
 
#define FLSH fflush(stdout)
#define fileIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#define PRECISION(x) cout << fixed << setprecision(x); 
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
// ----------------</Defines and typedefs>----------------
 
// -------------------<Debugging stuff>-------------------
#define TRACE
 
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
 
// ------------------</Debugging stuff>-------------------
 
// ------------------------<Consts>-----------------------
const int MAXN = 1000005;
const int SQRTN = 1003;
const int LOGN = 22;
const double PI=acos(-1);
const int INF = 1000000000;
const int MOD = 1000000007;
const int FMOD = 998244353;
const double eps = 1e-9;
 
// -----------------------</Consts>-----------------------
 
// -------------------------<RNG>-------------------------
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.
 
// ------------------------</RNG>-------------------------
 
// -----------------<Modular Arithmetic>------------------
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){ll res=(ll)a*b;return(res>=c?res%c:res);}
ll mulmod(ll a,ll b, ll m){ll q = (ll)(((LD)a*(LD)b)/(LD)m);ll r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template<typename T>T expo(T e, T n){T x=1,p=e;while(n){if(n&1)x=x*p;p=p*p;n>>=1;}return x;}
template<typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;\
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T>T mod_inverse(T a, T n){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));}
 
// -----------------</Modular Arithmetic>-----------------
// --------------------------------------------------</TEMPLATE>--------------------------------------------------
 

bool next_perm(int L[], int n){ //array and size, note that iterator implementation is in STL as well
	int i = n-1;
	while(i>=0 && L[i] >= L[i+1]){
		i-=1;
	}
	if (i == -1) return false;
	int j = i+1;
	while (j < n and L[j] > L[i]){
        j += 1;
    }
    j -= 1;
    int temp = L[i];
    L[i]=L[j];
    L[j] = temp;
    int left = i + 1;
    int right = n - 1;
    while (left < right){
    	int temp = L[left];
    	L[left]=L[right];
    	L[right] = temp;
        left += 1;
        right -= 1;
    }
    return true;
}

//----------------SegTree implementations-------------------------------
int t[4*MAXN];
//Constructing SegTree - use build(a, 1, 0, n-1, t) in original program, n = size of a (this builds t with array indices from tl to tr, root vertex v)
void buildseg(int a[], int v, int tl, int tr, int t[]) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        buildseg(a, v*2, tl, tm, t);
        buildseg(a, v*2+1, tm+1, tr, t);
        t[v] = t[v*2] + t[v*2+1];
    }
}
//Sum Query - use sumseg(1, 0, n-1, leftIndex, rightIndex, t); (this finds sum of array elements with indices from l to r, between tl and tr, with root vertex v)
int sumseg(int v, int tl, int tr, int l, int r, int t[]) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sumseg(v*2, tl, tm, l, min(r, tm), t)
           + sumseg(v*2+1, tm+1, tr, max(l, tm+1), r, t);
}
//Update Query - use updateseg(1, 0, n-1, positionInArraya, newvalue, t); (updates indices of t from tl to tr according to the new value at position)
void updateseg(int v, int tl, int tr, int pos, int new_val, int t[]) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updateseg(v*2, tl, tm, pos, new_val, t);
        else
            updateseg(v*2+1, tm+1, tr, pos, new_val, t);
        t[v] = t[v*2] + t[v*2+1];
    }
}


int m, n, k;

int f(int x){
    int sum = 0;
    for(int i = 1; i<=n; i++){
        sum += min(m, (x-1)/i);
    }
    return sum;
}

signed main(){
    cin>>n>>m>>k;
    int count = m*n;
    int first = 0;
    while(count>0){
        int it = first;
        int step = count/2;
        it+=step;
        if(f(it+1)<k){
            first=++it;
            count-=step+1;
        }
        else count = step;
    }
    cout<<first;
}