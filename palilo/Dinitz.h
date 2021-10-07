/**
 * @Description: flow_t을 고를 땐 '유량의 총 합'을 커버할 수 있도록 해야 함.
 * 모르겠으면 그냥 long long 씁시다.
 * @Usage: dfs(), bfs()는 내부적으로 쓰이는 거라 신경 ㄴ
 * add_edge(u, v, c): u -> v로 가는 용량 c짜리 간선 추가
 * max_flow(): src -> sink의 최대 유량 return
 */
using flow_t = int;

struct edge {
    int v, rev;
    flow_t capa;
    edge(int _v, int _rev, flow_t _capa) : v(_v), rev(_rev), capa(_capa) {}
};

const flow_t FLOW_MAX = numeric_limits<flow_t>::max();
int n, src = -1, sink = -1;

vector<vector<edge>> adj(n);
vector<int> level(n), ptr(n);

void add_edge(int u, int v, flow_t c) {
    assert(0 <= u and u < n and 0 <= v and v < n);
    adj[u].emplace_back(v, adj[v].size(), c);
    adj[v].emplace_back(u, adj[u].size() - 1, 0);
}

int bfs() {
    fill(level.begin(), level.end(), 0);
    level[src] = 1;
    queue<int> q;
    q.emplace(src);
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        for (const auto& [v, rev, capa] : adj[u])
            if (capa && !level[v]) {
                level[v] = level[u] + 1;
                q.emplace(v);
            }
    }
    return level[sink];
}
flow_t dfs(int u, flow_t f) {
    if (u == sink) return f;
    for (int &i = ptr[u], sz = adj[u].size(); i < sz; ++i) {
        auto& [v, rev, capa] = adj[u][i];
        if (capa && level[u] + 1 == level[v])
            if (flow_t d = dfs(v, min(f, capa)); d) {
                capa -= d;
                adj[v][rev].capa += d;
                return d;
            }
    }
    return 0;
}

flow_t max_flow() {
    flow_t ret = 0;
    for (flow_t f; bfs();) {
        fill(ptr.begin(), ptr.end(), 0);
        while ((f = dfs(src, FLOW_MAX))) ret += f;
    }
    return ret;
}