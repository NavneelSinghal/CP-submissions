#include <bits/stdc++.h>
using namespace std;

#define int long long
#define REP(i, n) for(int i = 0; i < (int) n; i++)

int n, m, k;
int visited[1000][1000];
string a[1000];

pair<int, int> dir[] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

bool check(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y, int col){
	if(visited[x][y] == 0){
		visited[x][y] = col;
		for(int i = 0; i < 4; i++){
			int nx = x + dir[i].first;
			int ny = y + dir[i].second;
			if(check(nx, ny) && a[nx][ny] == '.' && visited[nx][ny]==0){
				dfs(nx, ny, col);
			}
		}
	}
}

signed main() {
	
	cin >> n >> m >> k;
	
	REP(i, n) cin >> a[i];
	
	int col = 1;
	
	REP(i, n) REP(j, m){
		if(visited[i][j] == 0 && a[i][j] == '.'){
			dfs(i, j, col);
			col++;
		}
	}
	
	vector<int> num(col+1);
	
	REP(i, n) REP(j, m){
		if(a[i][j] == '.'){
			REP(k, 4){
				int nx = i + dir[k].first, ny = j + dir[k].second;
				if(check(nx, ny) && a[nx][ny] == '*'){
					num[visited[i][j]]++;
				}
			}
		}
	}
	
	
	REP(i, k){
		int x, y;
		cin >> x >> y;
		--x, --y;
		cout << num[visited[x][y]] << "\n";
	}
}
