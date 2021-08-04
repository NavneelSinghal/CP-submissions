#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")

#include <bits/stdc++.h>

#ifdef DEBUG
    #include "../debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        string s;
        cin >> s;
        int n = s.size();
        constexpr int block_size = 300;
        vector<array<int, 26>> block_prefixes(s.size());
        array<int, 26> freq_empty;
        fill(begin(freq_empty), end(freq_empty), 0);
        int total_blocks = (s.size() + block_size - 1) / block_size;
        for (int i = 0; i < total_blocks; ++i) {
            int left = i * block_size;
            int right = (i + 1) * block_size - 1;
            if (right >= n) right = n - 1;
            auto freq = freq_empty;
            for (int j = left; j <= right; ++j) freq[s[j] - 'a']++, block_prefixes[j] = freq;
        }
        auto join_blocks = [](const array<int, 26>& a, const array<int, 26>& b) {
            auto c = a;
            for (int i = 0; i < 26; ++i) c[i] += b[i];
            return c;
        };
        auto work = [](const array<int, 26>& a) {
            int distinct = 0;
            for (int i = 0; i < 26; ++i) distinct += (a[i] != 0);
            return distinct;
        };
        int q;
        cin >> q;
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int pos;
                char c;
                cin >> pos >> c;
                pos--;
                s[pos] = c;
                int block_id = pos / block_size;
                int block_end = min(n - 1, (block_id + 1) * block_size - 1);
                auto prv = freq_empty;
                if (pos % block_size) prv = block_prefixes[pos - 1];
                for (int j = pos; j <= block_end; ++j) {
                    prv[s[j] - 'a']++;
                    block_prefixes[j] = prv;
                }
            } else {
                int l, r;
                cin >> l >> r;
                --l, --r;
                int block_id_l = l / block_size;
                int block_id_r = r / block_size;
                if (block_id_l == block_id_r) {
                    auto freq = freq_empty;
                    for (int i = l; i <= r; ++i) {
                        freq[s[i] - 'a']++;
                    }
                    cout << work(freq) << '\n';
                } else {
                    auto chunk = freq_empty;
                    for (int i = block_id_l + 1; i < block_id_r; ++i) {
                        chunk = join_blocks(chunk, block_prefixes[(i + 1) * block_size - 1]);
                    }
                    chunk = join_blocks(chunk, block_prefixes[r]);
                    auto pre = freq_empty;
                    if (l % block_size) pre = block_prefixes[l - 1];
                    auto left_thing = block_prefixes[(block_id_l + 1) * block_size - 1];
                    for (int i = 0; i < 26; ++i) left_thing[i] -= pre[i];
                    chunk = join_blocks(chunk, left_thing);
                    cout << work(chunk) << '\n';
                }
            }
        }
    }
}
