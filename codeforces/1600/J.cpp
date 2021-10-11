// not my submission (just to check TLE)
// original submission: https://codeforces.com/contest/1600/submission/131503164
#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>
#define ll int

ll factory[1009][1009], vis[1009][1009];
ll rooms[1009 * 1009];
ll n, m, rs = 0;

struct pair {
    ll F;
    ll S;
} typedef pair;
pair moves[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

ll ct = 0;
void dfs(ll x, ll y) {
    if (vis[x][y]) return;
    vis[x][y] = 1;
    ct++;
    for (ll d = 0; d < 4; d++) {
        if (!((factory[x][y] >> d) & 1)) dfs(x + moves[d].F, y + moves[d].S);
    }
}

void merge(ll* ar, ll l, ll m, ll r) {
    ll i = 0, j = 0, k = l;
    ll n1 = m - l + 1;
    ll n2 = r - m;
    ll L[n1], R[n2];
    for (ll i = 0; i < n1; i++) L[i] = ar[l + i];
    for (ll j = 0; j < n2; j++) R[j] = ar[m + 1 + j];

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            ar[k++] = L[i++];
        else
            ar[k++] = R[j++];
    }
    while (i < n1) ar[k++] = L[i++];
    while (j < n2) ar[k++] = R[j++];
}

void Sort(ll* ar, ll l, ll r) {
    if (r > l) {
        ll mid = l + (r - l) / 2;
        Sort(ar, l, mid);
        Sort(ar, mid + 1, r);
        merge(ar, l, mid, r);
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < m; j++) scanf("%d", &factory[i][j]);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (vis[i][j]) continue;
            dfs(i, j);
            if (ct > 0) rooms[rs++] = ct;
            ct = 0;
        }
    }

    Sort(rooms, 0, rs - 1);
    for (ll i = 0; i < rs; i++) {
        printf("%d ", rooms[rs - 1 - i]);
    }
    printf("\n");
}

int main() {
    solve();
    return 0;
}
