// https://codeforces.com/problemset/problem/20/C
// По условию задачи все веса неотрицательные => можем применить алгоритм Дейкстры.
//
// В задаче указано, что могут быть петли и кратные ребра.
// Тут есть 2 варианта:
// 1) при считывании графа исключать петли сразу же и сохранять только минимальное из кратных ребер.
// 2) но, в целом, алгоритм Дейкстры и так справляется с петлями и кратные ребрами.
// В приведенном решении выбран 2-ой вариант, т.е. при считывании графа все сохраняем (и петли, и ребра).
// Рассмотрим более подробно про петли и кратные ребра.
// Если веса > 0, то в мин куче они будут более приоритетны, соответственно, мы в первую очередь обработаем минимальное из кратных ребер.
// А в случае петли, то такое ребро не попадет в кучу, т.к. суммарная длина от стартовой вершины до текущей, где есть петля, только увеличится (см. "if (curDist + w >= minDist[to]) continue;")
// Если какие-то веса == 0, то в случае кратных ребер мы добавим только одно из них, а остальные будут пропущены.
// А в случае петли, опять же из-за "if (curDist + w >= minDist[to]) continue;" мы просто пропустим эту петлю.
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = std::numeric_limits<ll>::max();

void solve() {
	ll n, m;
	cin >> n >> m;
	vector<vector<pair<ll, ll>>> g(n, vector<pair<ll, ll>>());
	for (int i = 0; i < m; i++) {
		ll a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		g[a].push_back(make_pair(b, w));
		g[b].push_back(make_pair(a, w));
	}
	
	// Use the Dijkstra's algorithm
	vector<ll> parent(n, -1);
	vector<ll> minDist(n, INF);
	// min-heap: {dist, vertex}
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
	minDist[0] = 0;
	parent[0] = -1;
	pq.push(make_pair(minDist[0], 0));
	while (!pq.empty()) {
		ll curDist = pq.top().first;
		ll curVertex = pq.top().second;
		pq.pop();

		// Для оптимизации можно указать так:
		//if (minDist[curVertex] < curDist) continue;
		// т.к. если minDist[curVertex] < curDist, то curVertex уже ранее был рассмотрен
		// (в мин куче эта вершина была более приоритетной). Но, в целом, это не обязательно,
		// потому что ниже в цикле мы просто рассмотрим все его ребра и убедимся, что для его соседей
		// minDist уже обновлен, поэтому по всем соседям будет continue.

		for (const auto& edge : g[curVertex]) {
			ll to = edge.first;
			ll w = edge.second;
			if (curDist + w >= minDist[to]) continue;

			minDist[to] = curDist + w;
			parent[to] = curVertex;
			pq.push(make_pair(minDist[to], to));
		}
	}

	// define the path
	if (parent[n-1] == -1) {
		cout << "-1\n";
	} else {
		vector<long> path;
		long vertex = n-1;
		while (vertex != -1) {
			path.push_back(vertex);
			vertex = parent[vertex];
		}
		for (auto it = path.rbegin(); it != path.rend(); it++) {
			cout << (*it) + 1 << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
	return 0;
}
