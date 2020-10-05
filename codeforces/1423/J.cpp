#include <bits/stdc++.h>
using namespace std;

#define int long long

template <unsigned Mod = 998244353> 
struct Modular {
    using M = Modular;
    unsigned v;
    Modular(long long a = 0) : v((a %= Mod) < 0 ? a + Mod : a) {}
    M operator-() const { return M() -= *this; }
    M& operator+=(M r) { if ((v += r.v) >= Mod) v -= Mod; return *this; }
    M& operator-=(M r) { if ((v += Mod - r.v) >= Mod) v -= Mod; return *this; }
    M& operator*=(M r) { v = (uint64_t)v * r.v % Mod; return *this; }
    M& operator/=(M r) { return *this *= pwr(r, Mod - 2); }
    friend M operator+(M l, M r) { return l += r; }
    friend M operator-(M l, M r) { return l -= r; }
    friend M operator*(M l, M r) { return l *= r; }
    friend M operator/(M l, M r) { return l /= r; }
    friend bool operator==(M l, M r) { return l.v == r.v; }
    friend bool operator!=(M l, M r) { return l.v != r.v; }
    friend ostream& operator<<(ostream& os, M a) { return os << a.v; }
    friend istream& operator>>(istream& is, M &a) { int64_t w; is >> w; a = M(w); return is; }
};

const int mod = 1e9 + 7;

using mint = Modular<mod>;

void solve() {
    int n;
    cin >> n;
    n /= 2;
    n += 2;
    mint m = (n + 1) / 2;
    mint o = (n) / 2;
    cout << m * o << '\n';
}

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
