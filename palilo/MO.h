/**
 * Description: dfs에서 노드에 들어가고 나갈 때마다 in-time, out-time을 기록했다면 $(u, v), {in_u \leq \in_v}$ 사이의 경로는...
 * $u = lca$일 경우, $[in_u, in_v]$.
 * $u \neq lca$일 경우, &[out_u, in_v] + in_{lca}$
 * Usage: array일 경우 add(), del()로 원소의 추가/삭제를 하면 돤다.
 * tree일 경우 add(), del()은 쓰면 안된다. 어떤 원소를 추가/삭제 하고 싶으면 flip()을 쓰면 된다.
 * Time: O(N \sqrt Q)
 */

struct query_t {
    int l, r, id;
    int lca;
    // ^ if tree
};

void add(int id) {}
void del(int id) {}
int calc() {}

// 여기서부터는 tree인 경우에만
vector<int> adj[MX_N];
int sz[MX_N], in[MX_N], out[MX_N], par[MX_N], top[MX_N], tour[MX_N << 1];
int tick;
bitset<MX_N> visited {};

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
    vector<query_t> q(m);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v, --u, --v;
        if (in[u] > in[v]) swap(u, v);
        auto lca = get_lca(u, v);
        u == lca ? (q[i].l = in[u], q[i].lca = -1) : (q[i].l = out[u], q[i].lca = lca);
        q[i].r = in[v] + 1, q[i].id = i;
    }
    constexpr int sq = 350;
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        if (a.l / sq != b.l / sq) return a.l < b.l;
        return a.l / sq & 1 ? a.r > b.r : a.r < b.r;
    });
    vector<int> ans(m);
    int pl = q[0].l, pr = q[0].l;
    for (const auto [l, r, id, lca] : q) {
        while (l < pl) flip(tour[--pl]); // 무조건 이거 먼저
        while (pr < r) flip(tour[pr++]); // 무조건 이거 먼저
        while (pl < l) flip(tour[pl++]); // 무조건 이거 나중에
        while (r < pr) flip(tour[--pr]); // 무조건 이거 나중에
        if (~lca) flip(lca);
        ans[id] = res;
        if (~lca) flip(lca);
    }
}
