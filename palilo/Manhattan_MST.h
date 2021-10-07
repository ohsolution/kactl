/**
 * Description: point 중 Manhattan_MST에 포함될 '후보 point' return (<= 4n)
 * Usage: T(distace_t), U(point_t);
 * return값에 Kruskal 쓰면 진짜 Manhattan_MST가 나온다.
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