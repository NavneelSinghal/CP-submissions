#include <bits/stdc++.h>
 
#define FASTIO
#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)
 
#ifdef FASTIO
#define scanf abacaba
#define printf abacaba
#endif
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
using namespace std;
 
template<typename T> T mo(T x, T y) { x %= y; return x <= 0 ? x + y : x; }
 
vector<int> cl[26], cr[26];
vector<int> fl, fr;
 
int main() {
#ifdef FASTIO
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            cl[s[i] - 'a'].push_back(i);
        } else {
            fl.push_back(i);
        }
    }
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            cr[s[i] - 'a'].push_back(i);
        } else {
            fr.push_back(i);
        }
    }
    vector<pair<int, int> > ans;
    for (int i = 0; i < 26; i++) {
        while (!cl[i].empty() && !cr[i].empty()) {
            int x = cl[i].back();
            cl[i].pop_back();
            int y = cr[i].back();
            cr[i].pop_back();
            ans.emplace_back(x, y);
        }
    }
    for (int i = 0; i < 26; i++) {
        while (!cl[i].empty() && !fr.empty()) {
            int x = cl[i].back();
            cl[i].pop_back();
            int y = fr.back();
            fr.pop_back();
            ans.emplace_back(x, y);
        }
    }
    for (int i = 0; i < 26; i++) {
        while (!fl.empty() && !cr[i].empty()) {
            int x = fl.back();
            fl.pop_back();
            int y = cr[i].back();
            cr[i].pop_back();
            ans.emplace_back(x, y);
        }
    }
    for (int i = 0; i < (int)min(fl.size(), fr.size()); i++) {
        ans.emplace_back(fl[i], fr[i]);
    }
    cout << ans.size() << "\n";
    for (auto v : ans) {
        cout << v.first + 1 << " " << v.second + 1 << "\n";
    }
    return 0;
}
 
