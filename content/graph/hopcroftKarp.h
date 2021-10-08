/**
 * Author: ohsolution
 * Date: 2021-10-08
 * Description: 
 * Time: O(\sqrt{V}E)
 */
#pragma once

vector <int> adj[max_v];
int n,m, match[max_v], dist[max_v];

bool bfs() {
	queue<int>bq;
	fa(i, 1, n + 1) {
		if (!match[i]) dist[i] = 0, bq.push(i);
		else dist[i] = INF;
	}

	dist[0] = INF;

	while (bq.size()) {
		int u = bq.front(); bq.pop();

		if (u) for (auto& x : adj[u]){
			if (dist[match[x]] == INF) {
				dist[match[x]] = dist[u] + 1;
				bq.push(match[x]);
			}
		}
	}

	return dist[0] != INF;
}

bool dfs(int u) {
	if (!u) return true;

	for (auto& x : adj[u]) {
		if (dist[match[x]] == dist[u] + 1 && dfs(match[x])) {
			match[x] = u, match[u] =x;
			return true;
		}
	}

	dist[u] = INF;
	return false;
}

int main() {	
	ci(n >> m);

	// match i(left) to i+n(right)
	fa(i, 1, n + 1) {
		int x; ci(x); 
		while (x--) {
			int y; ci(y); y += n;
			adj[i].push_back(y);
		}
	}

	int ans = 0;

	while (bfs()) {
		fa(i, 1, n + 1) if (!match[i] && dfs(i)) ++ans;
	}

	co(ans);

	return 0;
}
