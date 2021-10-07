
struct edge
{
	int a, b, cap, flow, cost;
};

vector<edge> ve;
vector<int> adj[max_v];
int idx[max_v], dist[max_v],inq[max_v],vist[max_v],S,T;

auto addedge = [&](int a, int b, int cap, int cost)
{
	edge e1 = { a,b,cap,0,cost };
	edge e2 = { b,a,0,0,-cost };
	adj[a].push_back(ve.size());
	ve.push_back(e1);
	adj[b].push_back(ve.size());
	ve.push_back(e2);
};

auto spfa = [&]()
{
	memset(dist, 0x3f, sizeof(dist));
	memset(inq, 0, sizeof(inq));

	queue<int> bq; bq.push(S);
	dist[S] = 0; inq[S] = 1;
	while (bq.size())
	{
		int u = bq.front(); bq.pop(); inq[u] = 0;

		for (auto& v : adj[u])
		{
			auto c = ve[v];
			if (c.flow < c.cap && (dist[c.b] > dist[u] + c.cost))
			{
				dist[c.b] = dist[u] + c.cost;
				if (!inq[c.b])bq.push(c.b), inq[c.b] = 1;
			}
		}
	}

	return dist[T] != INF;
};

function<int(int, int)> dfs = [&](int u, int f)
{
	if (!f) return 0;
	vist[u] = 1;
	if (u == T) return f;

	for (; idx[u] < adj[u].size(); ++idx[u])
	{
		int v = adj[u][idx[u]];
		auto c = ve[v];

		if (dist[c.b] != dist[u] + c.cost || vist[c.b]) continue;

		if (int flow = dfs(c.b, min(f, c.cap - c.flow)))
		{
			ve[v].flow += flow;
			ve[v ^ 1].flow -= flow;
			return flow;
		}
	}

	return 0;
};

auto run = [&]()
{
	int total_cost = 0;
	int total_flow = 0;

	while (spfa())
	{
		memset(idx, 0, sizeof(idx));
		memset(vist, 0, sizeof(vist));
		while (int f = dfs(S, INF))
		{
			total_cost += dist[T] * f;
			total_flow += f;
			memset(vist, 0, sizeof(vist));
		}
	}
};
