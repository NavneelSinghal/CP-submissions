#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    
    vector<vector<int>> a2(n), a5(n);
    for(auto &v : a2) v.resize(n);
    for(auto &v : a5) v.resize(n);
    
    bool iszero = false;
    int zeroi = -1, zeroj = -1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            if(x == 0){
                x = 10;
                iszero = true;
                zeroi = i;
                zeroj = j;
            }
            while(x % 2 == 0){
                a2[i][j]++;
                x >>= 1;
            }
            while(x % 5 == 0){
                a5[i][j]++;
                x /= 5;
            }
        }
    }

    //1 is for left, -1 for up
    vector<vector<int>> dir2(n, vector<int>(n)), dir5(n, vector<int>(n)), dp2(n, vector<int>(n)), dp5(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dp2[i][j] = a2[i][j];
            dp5[i][j] = a5[i][j];
            if(i == 0 && j != 0){
                dir2[i][j] = 1;
                dir5[i][j] = 1;
                dp2[i][j] += dp2[i][j-1];
                dp5[i][j] += dp5[i][j-1];
            }
            else if(i != 0 && j == 0){
                dir2[i][j] = -1;
                dir5[i][j] = -1;
                dp2[i][j] += dp2[i-1][j];
                dp5[i][j] += dp5[i-1][j];
            }
            else if(i != 0 && j != 0){
                if(dp2[i-1][j] < dp2[i][j-1]){
                    dir2[i][j] = -1;
                    dp2[i][j] += dp2[i-1][j];
                }
                else{
                    dir2[i][j] = 1;
                    dp2[i][j] += dp2[i][j-1];
                }
                if(dp5[i-1][j] < dp5[i][j-1]){
                    dir5[i][j] = -1;
                    dp5[i][j] += dp5[i-1][j];
                }
                else{
                    dir5[i][j] = 1;
                    dp5[i][j] += dp5[i][j-1];
                }
            }
        }
    }

    int ans = min(dp5[n-1][n-1], dp2[n-1][n-1]);
    if(iszero){
        ans = min(ans, 1ll);
    }
    cout << ans << endl;
    if(iszero && ans == 1){
        for(int i = 0; i < zeroi; i++){
            cout << "D";
        }
        for(int j = 0; j < n-1; j++){
            cout << "R";
        }
        for(int i = zeroi; i < n-1; i++){
            cout << "D";
        }
        cout << "\n";
    }
    else{
        string out;
        if(ans == dp5[n-1][n-1]){
            int i = n-1;
            int j = n-1;
            while(i != 0 || j != 0){
                if(dir5[i][j] == 1){
                    out += "R";
                    j--;
                }
                else{
                    out += "D";
                    i--;
                }
            }
        }
        else{
            int i = n-1;
            int j = n-1;
            while(i != 0 || j != 0){
                if(dir2[i][j] == 1){
                    out += "R";
                    j--;
                }
                else{
                    out += "D";
                    i--;
                }
            }
        }
        reverse(out.begin(), out.end());
        cout << out << "\n";
    }
}

