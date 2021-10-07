/**
 * Description: record in_time and out_time in dfs. the path of $(u, v), {in_u \leq \in_v}$ is ...
 * if $u = lca$, $[in_u, in_v]$.
 * if $u \neq lca$, &[out_u, in_v] + in_{lca}$
 * Usage:
 * if array: just use add(), del().
 * if tree: NEVER USE add(), del(). only use flip() for both
 * Time: O(N \sqrt Q)
 */
struct query_t {
    int l, r, id, lca;
};

void add(int id) {}
void del(int id) {}
int calc() {}

// < if tree >
vector<int> adj[MX_N];
int sz[MX_N], in[MX_N], out[MX_N], par[MX_N], top[MX_N], tour[MX_N << 1];
int tick;
bitset<MX_N> visited {};
// </if tree >

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
    in[u] = tick, tour[tick] = u;
    ++tick;
    bool heavy = true;
    for (const auto& v : adj[u]) {
        top[v] = heavy ? top[u] : v;
        hld(v);
        heavy = false;
    }
    out[u] = tick, tour[tick] = u;
    ++tick;
}

int get_lca(int u, int v) {
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]])
            swap(u, v);
    }
    return in[u] < in[v] ? u : v;
}

void flip(int id) {
    // if tree
    visited[id] ? del(id) : add(id);
    visited[id].flip();
}

int main() {
    // example of Mo's on tree
    // how to initialize queries
    vector<query_t> q(m);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        if (in[u] > in[v]) swap(u, v);
        auto lca = get_lca(u, v);
        u == lca ? (q[i].l = in[u], q[i].lca = -1) : (q[i].l = out[u], q[i].lca = lca);
        q[i].r = in[v] + 1, q[i].id = i;
    }
    // how to sort...
    constexpr int sq = 350;
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        if (a.l / sq != b.l / sq) return a.l < b.l;
        return a.l / sq & 1 ? a.r > b.r : a.r < b.r;
    });
    // how to calculate answer...
    vector<int> ans(m);
    int pl = q[0].l, pr = q[0].l;
    for (const auto [l, r, id, lca] : q) {
        while (l < pl) flip(tour[--pl]);
        while (pr < r) flip(tour[pr++]);
        while (pl < l) flip(tour[pl++]);
        while (r < pr) flip(tour[--pr]);
        if (~lca) flip(lca);
        ans[id] = calc();
        if (~lca) flip(lca);
    }
}
