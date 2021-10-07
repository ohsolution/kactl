/**
 * Author: ohsolution
 * Date: 2021-10-08
 * Description:
 */

vector<pair<int,int>> adj[max_v]; // nxt, dist pair
int vist[max_v],sz[max_v];
int cp[max_v]; // centroid tree parent

// caution: when using hld together, it must not overlap with the sz array used in hld
int dfsz(int u, int par = -1) {	
	sz[u] = 1;
	for (auto& v : adj[u]) if (v.first != par && !vist[v.first]) sz[u] += dfsz(v.first, u);
	return sz[u];
}

int fc(int u, int csz, int par = -1){
	for (auto& v : adj[u]) if (v.first != par && !vist[v.first] && sz[v.first] > csz) return fc(v.first, csz, u);
	return u;
}

void go(int u,int trp){
	int csz = dfsz(u);
	int cen = fc(u, csz/2); // find centroid

	vist[cen] = 1;
	cp[cen] = trp; // setting parent centroid of cur cen

	vector<int> cur; 
	// After collecting the information of the subtrees into a map in several places with centroid as a disconnect point,
	// the merge can be performed on the logn.

	function<void(int,int)> getsub = [&](int u,int par) {
		cur.push_back(u);
		for (auto& v : adj[u]) if (v.first != par && !vist[v.first]) getsub(v.first, u);
	};

	for (auto& v : adj[cen]) if (!vist[v.first]) { 
		getsub(v.first, u);
		for (auto& x : cur) cout << x << " "; // print v.first subtree node
		cur.clear();
	}

	for (auto& v : adj[cen]) if (!vist[v.first]) go(v.first,cen); // go nxt centroid
}

// When given a white vertex v, the shortest distance from the other vertex.
int color[max_v];
multiset <int> xset[max_v]; // The set that collects the distances of the white vertices from the vertex.
int p[20][max_v],d[max_v];

int getdist(int u, int v) {
	return d[u] + d[v] - 2 * d[lca(u, v)];
}

// Change the color of node v of the centroid tree update.
void upd(int v) {	
	color[v] = !color[v];
	int i = v;
	int ct = 0;
	while (~i) {	
		int dist = getdist(i, v);
		if (color[v]) xset[i].insert(dist); // if color is white than ins
		else xset[i].erase(xset[i].find(dist)); // if changed color is black then erase
		i = cp[i]; // move to parent cent
	}
}

// Centroid tree query. Find the black vertex v and the shortest white vertex.
int query(int v) {
	int i = v;
	int ret = INF;
	int ct = 0;
	while (~i) {		
		int dist = getdist(i, v); // distance with current cent to v
		if (xset[i].size()) ckmin(ret, dist + *xset[i].begin()); // saved white point distance
		i = cp[i];
	}

	return ret == INF ? -1 : ret;
}
