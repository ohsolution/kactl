/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct SuffixArray {
	vi sa, lcp;
	
	vi ori, lg2;
	vector<vi> st;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
		x.push_back('\0');
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) {
				a = sa[i - 1], b = sa[i];
				x[b] = (y[a] == y[b] && a+j<n && b+j<n && y[a + j] == y[b + j]) ? p - 1 : p++;
			}
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
				i+k<n-1 && j+k<n-1 && s[i + k] == s[j + k]; k++);
				
		// lcp RMQ build
		lg2.resize(n + 1);
		lg2[0] = lg2[1] = 0;
		rep(i,2,n+1) lg2[i] = lg2[i >> 1] + 1;

		ori.resize(n);
		int dep = lg2[n];
		st.resize(n);
		rep(i,0,n) {
			ori[sa[i]] = i;
			st[i].resize(dep + 1);
			st[i][0] = lcp[i];
		}
		rep(j,1,dep+1) {
			for(int i = 0; i + (1 << (j - 1)) < n; ++i) {
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	int get_lcp(int l, int r) {
		if(l == r) return sa.size() - l - 1;
		l = ori[l], r = ori[r];
		if(l > r) swap(l, r);
		int j = lg2[r - l];
		return min(st[l + 1][j], st[r - (1 << j) + 1][j]);
	}
};
// sa[0] = str.size(), sa.size() = str.size() + 1
// lcp[i] = lcp(sa[i - 1], sa[i]), lcp[0] = 0
