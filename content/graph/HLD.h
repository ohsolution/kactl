/**
 * Author: palilo
 * Date: 2021-10-08
 * Description:
 * Usage: dfs(0); hld(0);
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

vector<vector<int>> adj(n);
vector<int> sz(n), in(n), par(n), top(n);
int tick = 0;

void dfs(int u) {
	sz[u] = 1;
	for (auto& v : adj[u]) {
		par[v] = u;
		adj[v].erase(find(adj[v].begin(), adj[v].end(), u)); // if bidirectional
		dfs(v);
		sz[u] += sz[v];
		if (sz[v] > sz[adj[u][0]]) {
			swap(v, adj[u][0]);
		}
	}
}

void hld(int u) {
	in[u] = tick++;
	bool heavy = true;
	for (const auto& v : adj[u]) {
		top[v] = heavy ? top[u] : v;
		hld(v);
		heavy = false;
	}
}

int query_path(int u, int v) {
	// int ret = 0;
	for (; top[u] != top[v]; u = par[top[u]]) {
		if (sz[top[u]] > sz[top[v]])
			swap(u, v);
		// ret += query(in[top[u]], in[u] + 1);
	}
	if (in[u] > in[v]) swap(u, v);
	// ret += query(in[u], in[v] + 1);		if vertex
	// ret += query(in[u] + 1, in[v] + 1);  if edge
	// return u;                            if lca
}

int query_subtree(int u) {
	// return query(in[u], in[u] + sz[u]);
}
