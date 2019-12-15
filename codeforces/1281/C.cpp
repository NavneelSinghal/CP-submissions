#include <bits/stdc++.h>
using namespace std;
 
const int M = 1e9 + 7;
 
int main() {
    int t;
    cin >> t;
    while(t--) {
        int x;
        cin >> x;
        string s;
        cin >> s;
        int len = s.size();
        for (int i = 0; i < x; i++) {
            int k = s[i] - '0';
            if ((int) s.size() < x) {
                for (int j = 1; j < k; j++) if ((int) s.size() < x) {
                    for (int l = i + 1; l < len; l++) if ((int) s.size() < x) {
                        s += s[l];
                    }
                }
            }
            int d = (len - i - 1 + M) % M;
            len = ((i + 1) + 1LL * d * k) % M;
        }
        cout << len << "\n";
    }
    return 0;
}
