/**
 * Author: palilo
 * Date: 2021-10-07
 * License: CC0
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Usage:
 *  TODO
 */
#pragma once

template <typename T>
class binary_indexed_tree {
	const size_t n;
	vector<T> tree;

public:
	binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}
	// a[i] += val
	void update(size_t i, T val) {
		assert(0 <= i and i <= n);
		for (++i; i <= n; i += i & -i)
			tree[i] += val;
	}
	// return the sum of the range [0, i)
	T query(size_t i) const {
		assert(0 <= i and i <= n);
		T ret = 0;
		for (; i; i &= i - 1)
			ret += tree[i];
		return ret;
	}
	// return the sum of the range [l, r)
	T query(size_t l, size_t r) const {
		return query(r) - query(l);
	}
	// return a[i]
	T get(size_t i) const {
		assert(0 <= i and i < n);
		return i & 1 ? query(i, i + 1) : tree[i + 1];
	}
	// return minimum i s.t. sum[0...i] >= k
	size_t lower_bound(T k) const {
		size_t x = 0;
		for (size_t pw = 1 << 25; pw; pw >>= 1)
			if ((x | pw) <= n && tree[x | pw] < k)
				k -= tree[x |= pw];
		return x;
	}
	// return minimum i s.t. sum[0...i] > k
	size_t upper_bound(T k) const {
		size_t x = 0;
		for (size_t pw = 1 << 25; pw; pw >>= 1)
			if ((x | pw) <= n && tree[x | pw] <= k)
				k -= tree[x |= pw];
		return x;
	}
};
