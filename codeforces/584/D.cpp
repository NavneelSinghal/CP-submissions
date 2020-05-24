#include <bits/stdc++.h>
using namespace std;

#define int long long

using u64 = uint64_t;
using u128 = uint64_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

signed main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    if(n == 3){
        cout << 1 << endl << 3 << endl;
        return 0;
    }
    if(n == 5){
        cout << 1 << endl << 5 << endl;
        return 0;
    }
    if(n > 5){
        int p1 = -1;
        for(int i = 0; i < 1000; i += 2){
            if(MillerRabin(n - i)){
                p1 = n-i;
                break;
            }
        }
        assert(p1 != -1);
        int target = n - p1;
        if(target == 0){
            cout << 1 << endl << n << endl;
            return 0;
        }
        else if(target == 2){
            cout << 2 << endl << n-2 << " " << 2 << endl;
            return 0;
        }
        else{
            cout << 3 << endl;
            int N = 1000;
            vector<char> is_prime(N+1, true);
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i <= N; i++) {
                if (is_prime[i] && (long long)i * i <= N) {
                    for (int j = i * i; j <= N; j += i)
                        is_prime[j] = false;
                }
            }
            for(int i = 0; i < 1000; i++){
                if(is_prime[i] && is_prime[target - i]){
                    cout << p1 << " " << i << " " << target - i << endl;
                    return 0;
                }
            }
        }
    }

}

