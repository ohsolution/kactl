/**
 * Description: return candidate edges(w, u, v) of Manhattan_MST (<= 4n)
 * Usage: T(distace_t), U(point_t)
 * run Kruskal's to get the 'true' Manhattan_MST
 */
template <typename T, typename U>
vector<tuple<T, int, int>> manhattan_MST(const vector<U>& a) {
    vector<int> id(a.size());
    iota(id.begin(), id.end(), 0);
    vector<tuple<T, int, int>> edges;
    edges.reserve(n << 2);
    for (int t = 0; t < 4; ++t) {
        sort(id.begin(), id.end(), [&](auto& lhs, auto& rhs) {
            return a[lhs].x - a[rhs].x < a[rhs].y - a[lhs].y;
        });
        map<T, int, greater<T>> sweep;
        for (const auto& i : id) {
            for (auto it = sweep.lower_bound(a[i].y); it != sweep.end(); it = sweep.erase(it)) {
                int j = it->y;
                T dx = a[i].x - a[j].x, dy = a[i].y - a[j].y;
                if (dy > dx) break;
                edges.emplace_back(dx + dy, i, j);
            }
            sweep[a[i].y] = i;
        }
        for (auto& [x, y] : a) {
            if (t & 1) {
                x = -x;
            } else {
                swap(x, y);
            }
        }
    }
}
