/**
 * Author: palilo
 * Date: 2021-10-07
 * License: CC0
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 *  apply: for each x in [l, r) a[x] = b * a[x] + c
 *  prod: range sum
 * Time: O(\log N).
 * Usage:
 *  `e`, `off`   : identity element
 *  `op`         : unite two nodes
 *  `mapping`    : apply tag to node
 *  `composition`: unite two tags
 *  be careful for setting value `e`, it will used for...
 *  1. dummy nodes (out of range)
 *  2. initial value in `prod` and `op`
 */

#pragma once

template <typename node_t, typename tag_t>
class lazy_segtree {
	const node_t e {};      // change it
	const tag_t off {1, 0}; // change it
	const size_t n, height, size;
	vector<node_t> tree;
	vector<tag_t> lazy;

public:
	lazy_segtree(size_t n) : n(n), height(n ? __lg(n - 1) + 1 : 0), size(1 << height),
							 tree(size << 1, e), lazy(size, off) {}

	node_t& operator[](size_t i) { return tree[size + i]; }
	void build() {
		for (size_t i = size; i--;) {
			pull(i);
		}
	}
	void apply(size_t l, size_t r, tag_t f) {
		apply(l, r, f, 0, size, 1);
	}
	node_t prod(size_t l, size_t r) {
		return prod(l, r, 0, size, 1);
	}

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
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
	void apply(size_t ql, size_t qr, tag_t f, size_t l, size_t r, size_t i) {
		if (qr <= l || r <= ql) return;
		if (ql <= l && r <= qr) {
			all_apply(i, f);
			return;
		}
		if (lazy[i] != off) push(i);

		const auto m = (l + r) >> 1;
		apply(ql, qr, f, l, m, lson), apply(ql, qr, f, m, r, rson);
		pull(i);
	}
	node_t prod(size_t ql, size_t qr, size_t l, size_t r, size_t i) {
		if (qr <= l || r <= ql) return e;
		if (ql <= l && r <= qr) return tree[i];
		if (lazy[i] != off) push(i);

		const auto m = (l + r) >> 1;
		return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
	}
	void pull(size_t i) {
		tree[i] = op(tree[lson], tree[rson]);
	}
	void push(size_t i) {
		all_apply(lson, lazy[i]);
		all_apply(rson, lazy[i]);
		lazy[i] = off;
	}
	void all_apply(size_t i, tag_t f) {
		mapping(tree[i], f);
		if (i < size) composition(lazy[i], f);
	}
	node_t op(node_t lhs, node_t rhs) const {
		// return lhs + rhs;
	}
	void mapping(node_t& node, tag_t f) {
		// node = node * f.first + get_length(node) * f.second;
	}
	void composition(tag_t& tag, tag_t f) {
		// tag.first *= f.first;
		// tag.second = tag.second * f.first + f.second;
	}
};
