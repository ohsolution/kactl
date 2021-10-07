
int dfn[max_v], low[max_v], cn, ccn;
vector<int> adj[max_v];
vector<vector<int>> bcc;
vector<pair<int, int>> st;

function<void(int, int)> dfs = [&](int u, int p)
{
	dfn[u] = low[u] = cn++;

	for (auto& v : adj[u]) if (v != p)
	{
		if (dfn[v] < dfn[u]) st.push_back({ u,v });

		if (dfn[v]) ckmin(low[u], dfn[v]);
		else
		{
			dfs(v, u);
			ckmin(low[u], low[v]);
			if (low[v] >= dfn[u])
			{
				if (st.back().first == u && st.back().second == v) bcc[ccn].push_back(v);

				while (1)
				{
					pair<int,int> cur = st.back(); st.pop_back();
					bcc[ccn].push_back(cur.first);
					if (cur.first == u && cur.second == v) break;
				}

				++ccn;
			}

		}
	}
};

for(int i=0;i<n;++i) if (!dfn[i]) dfs(i, -1);
