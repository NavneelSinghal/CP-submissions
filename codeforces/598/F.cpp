#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll
typedef pair<long double, long double> pd;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < (int) n; i++)
#define INF 1000000000
#define eps 1e-10

vector<pd> vv;

inline int cmp(double x){
	return (x > eps) - (x < -eps);
}

long double dot(pd a, pd b){
	return a.F * b.F + a.S * b.S;
}

long double  length(pd a){
	return sqrt(dot(a, a));
}

long double cross(pd a, pd b){
	return a.F * b.S - a.S * b.F;
}

long double intersect(pd a, pd b, pd c, pd d){
	pd u = {a.F - c.F, a.S - c.S};
	return cross(d, u)/cross(b, d);
}

pd operator + (pd a, pd b) {return {a.F+b.F, a.S+b.S};}
pd operator - (pd a, pd b) {return {a.F-b.F, a.S-b.S};}

void segint(pd p, pd v, pd q, pd w){
	if(!cmp(cross(v, w))){
		if(!cmp(cross(v, q-p))){
			long double l = dot(v, q-p) / dot(v, v);
			long double r = dot(v, q+w-p) / dot(v, v);
			if(l > r) swap(l, r);
			vv.push_back({l, -1});
			vv.push_back({r, +1});
		}
	}
	else{
		long double tmp = intersect(q, w, p, v);
		if(cmp(tmp)>=0 && cmp(tmp-1)<=0){
			long double rr = 1;
			if(cmp(tmp) == 0 || cmp(tmp-1) == 0) rr = 0.5;
			tmp = intersect(p, v, q, w);
			vv.push_back({tmp, (cross(w, v) > 0)?-rr:rr});
		}
	}
}

signed main() {
	cout << setprecision(20) << fixed;
	int n, m;
	cin >> n >> m;
	vector<pd> pts(n+1);
	for(int i = 0; i < n; i++){
		cin >> pts[i].F >> pts[i].S;
	}
	pts[n] = pts[0];
	for(int j = 0; j < m; j++){
		pd a, b;
		cin >> a.F >> a.S >> b.F >> b.S;
		vv.clear();
		for(int i = 0; i < n; i++){
			segint(a, b-a, pts[i], pts[i+1]-pts[i]);
		}
		sort(vv.begin(), vv.end());
		long double ans = 0;
		long double k = 0;
		REP(i, vv.size()){
			k += vv[i].S;
			if(cmp(k)) ans += vv[i+1].F - vv[i].F;
		}
		ans *= length(b-a);
		cout << ans << "\n";
	}
}
