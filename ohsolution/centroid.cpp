
vector<pair<int,int>> adj[max_v]; // nxt, dist pair
int vist[max_v],sz[max_v];
int cp[max_v]; // centroid tree parent

int dfs(int u, int par = -1)
{
	sz[u] = 1;
	for (auto& v : adj[u]) if (v.first != par && !vist[v.first]) sz[u] += dfs(v.first, u);
	return sz[u];
}

int fc(int u, int csz, int par = -1)
{
	for (auto& v : adj[u]) if (v.first != par && !vist[v.first] && sz[v.first] > csz) return fc(v.first, csz, u);
	return u;
}

void go(int u,int trp)
{
	int csz = dfs(u);
	int cen = fc(u, csz/2); // find centroid

	vist[cen] = 1;
	cp[cen] = trp; // 해당 센트에 부모 센트로이드 설정 make centroid tree

	vector<int> cur; // 센트로이드를 단절점으로 하는 여러개에 서브트리들의 정보를 map으로 모은후 merge 를 logn 에 할 수 있다.

	function<void(int,int)> getsub = [&](int u,int par)
	{
		cur.push_back(u);
		for (auto& v : adj[u]) if (v.first != par && !vist[v.first]) getsub(v.first, u);
	};

	for (auto& v : adj[cen]) if (!vist[v.first])
	{
		getsub(v.first, u);
		for (auto& x : cur) cout << x << " "; // print v.first subtree node
		cur.clear();
	}

	for (auto& v : adj[cen]) if (!vist[v.first]) go(v.first,cen); // go nxt centroid
}

// 한 흰색정점 v가 주어질 때 다른 흰색정점과의 최단거리
int color[max_v];
multiset <int> xset[max_v]; // 해당 정점으로부터 흰색정점들의 거리를 모은 set
int p[20][max_v],d[max_v];

int getdist(int u, int v)
{
	return d[u] + d[v] - 2 * d[lca(u, v)];
}

void upd(int v) // 센트로이드 트리 update v번 노드의 색깔을 바꾼다.
{	
	color[v] = !color[v];
	int i = v;
	int ct = 0;
	while (~i)
	{	
		int dist = getdist(i, v);
		if (color[v]) xset[i].insert(dist); // 흰색이면 ins
		else xset[i].erase(xset[i].find(dist)); // 검은색으로 바꼈으면 erase
		i = cp[i]; // 해당 센트 부모로 이동
}
}

int query(int v) // 센트로이드 트리 query 검은색 정점 v와 최단거리인 흰색정점 구하기
{
	int i = v;
	int ret = INF;
	int ct = 0;
	while (~i)
	{		
		int dist = getdist(i, v); // v와 현재 센트와의 거리
		if (xset[i].size()) ckmin(ret, dist + *xset[i].begin()); // 셋에 저장되어있는 최소 흰색정점 거리
		i = cp[i];
	}

	return ret == INF ? -1 : ret;
}
