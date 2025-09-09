// https://codeforces.com/problemset/problem/1106/D
// Здесь не можем использовать DFS, т.к. требуется
// лексикографически минимальный ответ.
// Я изначально хотел отсортировать (использовал set)
// и запустить DFS по отсортированным соседям, но это некорректный подход,
// Контрпример: [1, 2], [1, 3], [2, 4].
// DFS пойдет 1 -> 2 -> 4, потом вернемся в 1 и пойдем в 3.
// Правильно: 1 -> 2, возвращаемся в 1, -> 3, потом снова в 1, потом 1->2->4.

#include <bits/stdc++.h>

using namespace std;

vector<long> bfs(const vector<vector<long>>& g) {
	long n = g.size();
	vector<long> ans;
	vector<bool> used(n, false);
	priority_queue<long, vector<long>, greater<long>> q;
	q.push(0);
	used[0] = true;
	while (!q.empty()) {
		long f = q.top();
		q.pop();
		ans.push_back(f);
		for (long to : g[f]) {
			if (used[to]) continue;
			used[to] = true;
			q.push(to);
		}
	}
	return ans;
}

void solve() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	long n, m;
	cin >> n >> m;
	vector<vector<long>> g(n, vector<long>());
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--; // indexing from 0
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int v : bfs(g))
		cout << (v+1) << ' ';
	cout << '\n';
}

int main() {
	solve();
	return 0;
}
