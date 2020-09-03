/*
 ~ Author    : @tridib_2003
 ~ Title     : Road Reparation
 ~ Link      : https://cses.fi/problemset/task/1675/
*/

#include<bits/stdc++.h>
using namespace std;

#define ll                  long long
#define PI                  3.1415926535897932384626
#define MOD                 1000000007
#define vi                  vector<int>
#define mk(arr, n, type)    type *arr = new type[n];
#define FOR(a, c)           for (int(a) = 0; (a) < (c); (a)++)
#define w(x)                int x; cin >> x; while(x--)
#define FIO                 ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<pair<int, pair<int, int> > > edges;
int parent[100005];
int ranks[100005];

int findSet(int v) {
	if (parent[v] != v)
		parent[v] = findSet(parent[v]);
	return parent[v];
}

void performUnion(int v1Set, int v2Set) {
	if (ranks[v1Set] < ranks[v2Set])
		parent[v1Set] = v2Set;
	else if (ranks[v2Set] < ranks[v1Set])
		parent[v2Set] = v1Set;
	else {
		parent[v2Set] = v1Set;
		++ranks[v1Set];
	}
}

void reperationCost(int n, int m) {

	ll minCost = 0;

	sort(edges.begin(), edges.end());

	for (int i = 1; i <= n; ++i) {
		parent[i] = i;
		ranks[i] = 0;
	}

	int mstEdges = n - 1;

	vector<pair<int, pair<int, int> > > :: iterator itr;
	for (itr = edges.begin(); itr != edges.end(); ++itr) {

		int v1 = itr->second.first;
		int v2 = itr->second.second;

		int v1Set = findSet(v1);
		int v2Set = findSet(v2);

		if (v1Set != v2Set) {

			minCost += itr->first;

			performUnion(v1Set, v2Set);

			if (--mstEdges == 0)
				break;
		}
	}

	if (mstEdges)
		cout << "IMPOSSIBLE";
	else
		cout << minCost;
}

int main() {

	FIO;

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int src, dest, weight;
		cin >> src >> dest >> weight;
		edges.emplace_back(make_pair(weight, make_pair(src, dest)));
	}

	reperationCost(n, m);

	return 0;
}