/**
 * Author: palilo
 * Date: 2021-10-07
 * License: CC0
 * Description: Lazy Segment Tree - Gold Mine
 * Time: O(\log N).
 * Usage:
 * `e` : identity element
 * `op`: unite two nodes
 */

#pragma once

struct node_t {
    ll lmax, cmax, rmax, sum;
};

template <typename node_t>
class segtree {
    const node_t e {}; // change
    const size_t n, height, size;
    vector<node_t> tree;

public:
    segtree(size_t n) : n(n), height(n ? __lg(n - 1) + 1 : 0), size(1 << height), tree(size << 1, e) {}

    node_t& operator[](size_t i) { return tree[size + i]; }
    void build() {
        for (size_t i = size; i--;) {
            pull(i);
        }
    }
    void set(size_t idx, node_t val) {
        assert(0 <= idx and idx < n);
        tree[idx += size] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(size_t l, size_t r) const {
        assert(0 <= l and l <= r and r <= n);
        node_t lval = e, rval = e;
        for (l += size, r += size; l != r; l >>= 1, r >>= 1) {
            if (l & 1) lval = op(lval, tree[l++]);
            if (r & 1) rval = op(tree[--r], rval);
        }
        return op(lval, rval);
    }
    ll all_prod() const {
        return tree[1].cmax;
    }
    void clear() {
        fill(tree.begin(), tree.end(), e);
    }

private:
    inline int get_index(node_t& node) const { return &node - tree.data(); }
    inline int get_depth(node_t& node) const { return __lg(get_index(node)); }
    inline int get_height(node_t& node) const { return height - get_depth(node); }
    inline int get_length(node_t& node) const { return 1 << get_height(node); }
    inline int get_first(node_t& node) const {
        int idx = get_index(node);
        int dep = __lg(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
    }
    void pull(size_t i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    node_t op(node_t l, node_t r) const {
        // return node_t {
        //     .lmax = max(l.lmax, l.sum + r.lmax),
        //     .cmax = max({l.cmax, r.cmax, l.rmax + r.lmax}),
        //     .rmax = max(r.rmax, r.sum + l.rmax),
        //     .sum = l.sum + r.sum};
    }
};
