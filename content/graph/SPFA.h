/**
 * Author: Cube219
 * Date: 2021-10-08
 * Description: Calculates shortest paths from $st$ in a graph that might have negative edge weights.
 *  Return false if the graph has a negative cycle.
 */
#pragma once

constexpr ll INF = 9999999999999999;

vector<pair<int, ll>> g[1001];
ll dst[1001];
bool inq[1001];
int n, cycle[1001];

bool spfa(int st) {
    for(int i = 0; i < n; ++i) dst[i] = INF;
    dst[st] = 0;
    queue<int> q;
    q.push(st);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;
            if(dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                if(inq[nxt] == false) {
                    q.push(nxt);
                    inq[nxt] = true;
                }
                cycle[nxt]++;
                if(cycle[nxt] > n) {
                    return false;
                }
            }
        }
    }
    return true;
}
