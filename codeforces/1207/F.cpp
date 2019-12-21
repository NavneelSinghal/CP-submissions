#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;
#define maxn 500005
#define sq 269

int a[maxn];
int ans[sq+1][sq+1];
int t, q, x, y, i, sol;

void read(int &a) {
    static char c;
    c = getchar();
    if (c == '-') {
        a = 0;
        while (c = getchar(), c >= '0')
            a = (a << 3) + (a << 1) + (c - '0');
        a = -a;
    } else {
        a = c - '0';
        while (c = getchar(), c >= '0')
            a = (a << 3) + (a << 1) + (c - '0');
    }
}
 
void read(char &c) {
    c = getchar();
    getchar();
}
 
void read(string &s) {
    s = "";
    static char c;
    while (c = getchar(), c >= 'a')
        s += c;
}
 
void print(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) print(x / 10);
    putchar(x % 10 + '0');
}
 
void print(char c) {
    putchar(c);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	read(t);
	while(t--){
		read(q); read(x); read(y);
		if(q == 1){
			a[x] += y;
			for(i = 1; i <= sq; i++) ans[i][x % i] += y;
		}
		else{
			if(x > sq){
				sol = 0;
				for(i = y; i <= maxn; i+=x) sol += a[i];
				print(sol);
				putchar('\n');
			}
			else{
				print(ans[x][y]);
				putchar('\n');
			}
		}
	}
}
