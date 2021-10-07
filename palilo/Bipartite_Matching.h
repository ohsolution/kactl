int n, m;
vector<vector<int>> adj(n);
vector<int> match(n), rev(m);
vector<bool> visited(n);

bool dfs(int u) {
    visited[u] = true;
    for (const auto& v : adj[u]) {
        if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
            match[u] = v, rev[v] = u;
            return true;
        }
    }
    return false;
}

int maximum_matching() {
    for (bool update = true; update;) {
        fill(visited.begin(), visited.end(), false);
        update = false;
        for (int i = 0; i < n; ++i)
            if (match[i] == -1 && dfs(i))
                update = true;
    }
    return n - count(match.begin(), match.end(), -1);
}

// if index >= 0 -> left group
//    index < 0 -> right group
vector<int> minimum_vertex_cover() {
    vector<char> check(m);
    auto bfs = [&](int src) {
        queue<int> q;
        q.emplace(src);
        visited[src] = true;
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            for (const auto& v : adj[u])
                if (~rev[v] && !visited[rev[v]] && match[u] != v) {
                    check[v] = 1;
                    visited[rev[v]] = true;
                    q.emplace(rev[v]);
                }
        }
    };
    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < n; ++i)
        if (match[i] == -1 && !visited[i])
            bfs(i);
    vector<int> ret;
    ret.reserve(n - count(match.begin(), match.end(), -1));
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            ret.emplace_back(int(i));
    for (int i = 0; i < m; ++i)
        if (check[i])
            ret.emplace_back(~int(i));
    return ret;
}