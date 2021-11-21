/*
 ~ Author    : @tridib_2003
 ~ Title     : Counting Numbers
 ~ Link      : https://cses.fi/problemset/task/1194/
*/

#include<bits/stdc++.h>
using namespace std;

#define ll                  long long
#define ull                 unsigned long long
#define PI                  acos(-1)
#define MOD                 1000000007 // 998244353
#define EPS                 1e-9
#define vi                  vector<int>
#define vb                  vector<bool>
#define vvi                 vector<vector<int> >
#define vll                 vector<long long>
#define vvll                vector<vector<long long> >
#define pii                 pair<int, int>
#define pll                 pair<long long, long long>
#define vpii                vector<pair<int, int> >
#define vpll                vector<pair<long long, long long> >
#define pb                  push_back
#define eb                  emplace_back
#define mp                  make_pair
#define mk(arr, n, type)    type *arr = new type[n];
#define FOR(i, a, b)        for (int(i) = (a); (i) < (b); ++(i))
#define RFOR(i, a, b)       for (int(i) = (a)-1; (i) >= (b); --(i))
#define FORALL(i, a)        for (auto& (i) : (a))
#define print(a)            cout << a << '\n'
#define printall(a)         for (auto& (i) : (a)) cout << i << ' '
#define rsort(a)            sort((a).rbegin(), (a).rend())
#define w(x)                int x; cin >> x; while(x--)
#define all(c)              (c).begin(), (c).end()
#define sz(c)               (int)(c).size()
#define pqmx                priority_queue<int>
#define pqmn                priority_queue<int, vector<int>, greater<int> >
#define max3(a, b, c)       max((a), max((b), (c)))
#define min3(a, b, c)       min((a), min((b), (c)))
#define mx_all(c)           *max_element((c).begin(), (c).end())
#define mn_all(c)           *min_element((c).begin(), (c).end())
#define lwr_b(c, a)         lower_bound((c).begin(), (c).end(), (a)) - ((c).begin())
#define upr_b(c, a)         upper_bound((c).begin(), (c).end(), (a)) - ((c).begin())
#define FIO                 ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


static int dx[] = {0, 0, 1, -1};
static int dy[] = { -1, 1, 0, 0};
static char dir[] = {'L', 'R', 'D', 'U'};

int n, m, startX, startY, timeTaken;
bool isPossible;
string validPath;

vector<string> grid;
vector<vector<char> > path;
vector<vector<bool> > visited;
vector<vector<int> > monsterTime;

void init() {

	grid.clear();
	grid.resize(n);

	visited.clear();
	visited.resize(n);

	FOR (i, 0, n) {
		visited[i].resize(m, false);
	}

	monsterTime.clear();
	monsterTime.resize(n);

	FOR (i, 0, n) {
		monsterTime[i].resize(m, INT_MAX);
	}

	path.clear();
	path.resize(n);

	FOR (i, 0, n) {
		path[i].resize(m, 'X');
	}

	isPossible = false;
	validPath.clear();
}

void monster_bfs(queue<pii> q) {

	while (!q.empty()) {

		int k = sz(q);

		FOR (i, 0, k) {

			pii curr = q.front();
			q.pop();

			int currX = curr.first;
			int currY = curr.second;

			FOR (j, 0, 4) {
				int adjX = currX + dx[j];
				int adjY = currY + dy[j];

				if ((adjX >= 0 && adjX < n) && (adjY >= 0 && adjY < m) && !visited[adjX][adjY] && (grid[adjX][adjY] == '.')) {
					q.push({adjX, adjY});
					visited[adjX][adjY] = true;
					monsterTime[adjX][adjY] = monsterTime[currX][currY] + 1;
				}
			}
		}
	}
}

void findPath(int x, int y) {

	while (path[x][y] != 'A') {
		validPath += path[x][y];

		int idx;

		if (path[x][y] == 'L')
			idx = 1;
		else if (path[x][y] == 'R')
			idx = 0;
		else if (path[x][y] == 'D')
			idx = 3;
		else if (path[x][y] == 'U')
			idx = 2;

		x += dx[idx];
		y += dy[idx];
	}

	reverse(all(validPath));
}

void my_bfs(int x, int y) {

	visited.clear();
	visited.resize(n);

	FOR (i, 0, n) {
		visited[i].resize(m, false);
	}

	queue<pii> q;
	q.push({x, y});
	visited[x][y] = true;

	int currTime = 0;

	while (!q.empty()) {

		int k = sz(q);

		FOR (i, 0, k) {

			pii curr = q.front();
			q.pop();

			int currX = curr.first;
			int currY = curr.second;

			FOR (j, 0, 4) {
				int adjX = currX + dx[j];
				int adjY = currY + dy[j];

				if ((adjX >= 0 && adjX < n) && (adjY >= 0 && adjY < m) && !visited[adjX][adjY] && (grid[adjX][adjY] == '.') && (currTime + 1 < monsterTime[adjX][adjY])) {
					if (adjX == 0 || adjX == n - 1 || adjY == 0 || adjY == m - 1) {
						isPossible = true;
						timeTaken = currTime + 1;
						path[adjX][adjY] = dir[j];
						findPath(adjX, adjY);
						return;
					}

					q.push({adjX, adjY});
					visited[adjX][adjY] = true;
					path[adjX][adjY] = dir[j];
				}
			}
		}

		++currTime;
	}
}

void solve() {

	cin >> n >> m;

	init();

	queue<pii> todo;

	FOR (i, 0, n) {
		cin >> grid[i];

		FOR (j, 0, m) {
			if (grid[i][j] == 'A') {
				startX = i;
				startY = j;
				path[i][j] = 'A';
			}
			else if (grid[i][j] == 'M') {
				todo.push({i, j});
				visited[i][j] = true;
				monsterTime[i][j] = 0;
			}
		}
	}

	if (startX == 0 || startX == n - 1 || startY == 0 || startY == m - 1) {
		cout << "YES" << '\n' << 0;
		return;
	}

	monster_bfs(todo);
	my_bfs(startX, startY);

	if (isPossible)
		cout << "YES" << '\n' << timeTaken << '\n' << validPath;
	else
		cout << "NO";
}

int main() {

	FIO;

	int t = 1;
	// cin >> t;
	while (t--) {

		solve();
		cout << '\n';
	}

	return 0;
}
