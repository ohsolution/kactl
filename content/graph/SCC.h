/**
 * Author: Cube219
 * Date: 2021-10-08
 * License: CC0
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(g, n);
 * sccIdx[node] or sccs({0, 1, 3}, {2, 4}, ...)
 * Time: O(E + V)
 */
#pragma once

vector<vi> sccs;
vi d, st, sccIdx;
int dNum;
int dfs(vector<vi>& g, int cur) {
	d[cur] = dNum++;
	st.push_back(cur);
	int ret = d[cur];
	for(int nxt : g[cur]) {
		if(sccIdx[nxt] < 0) ret = min(ret, d[nxt] ? : dfs(g, nxt));
	}
	if(ret == d[cur]) {
		int top;
		sccs.push_back({});
		auto& scc = sccs.back();
		do {
			top = st.back(); st.pop_back();
			scc.push_back(top);
			sccIdx[top] = sccs.size();
		} while(top != cur);
	}
	return ret;
}
void scc(vector<vi>& g, int n)
{
	d.assign(n, 0); sccIdx.assign(n, -1); dNum = 1;
	rep(i,0,n) if (sccIdx[i] < 0) dfs(g, i);
}
