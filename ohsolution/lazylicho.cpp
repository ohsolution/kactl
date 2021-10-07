typedef long long ll;
const ll inf = 4e18;
struct LiChao  // Minimum line management If you want maximum management, you can put -ax-b instead of ax+b.
{
	struct Node {
		int l, r; ll a, b, mn, aa, bb;
		Node() { l = 0; r = 0; a = 0; b = inf; mn = inf; aa = 0; bb = 0; }
	};
	vector<Node> seg;
	ll _l, _r;
	LiChao(ll l, ll r) {
		seg.resize(2);
		_l = l; _r = r;
	}
	
	void propagate(int n, ll l, ll r) 
	{
		if (seg[n].aa || seg[n].bb) {
			if (l != r) {
				if (seg[n].l == 0) seg[n].l = seg.size(), seg.push_back(Node());
				if (seg[n].r == 0) seg[n].r = seg.size(), seg.push_back(Node());
				seg[seg[n].l].aa += seg[n].aa, seg[seg[n].l].bb += seg[n].bb;
				seg[seg[n].r].aa += seg[n].aa, seg[seg[n].r].bb += seg[n].bb;
			}
			seg[n].mn += seg[n].bb;
			seg[n].a += seg[n].aa, seg[n].b += seg[n].bb;
			seg[n].aa = seg[n].bb = 0;
		}
	}
	
	void insert(ll L, ll R, ll a, ll b, int n, ll l, ll r) 
	{
		if (r < L || R < l || L > R) return;
		if (seg[n].l == 0) seg[n].l = seg.size(), seg.push_back(Node());
		if (seg[n].r == 0) seg[n].r = seg.size(), seg.push_back(Node());
		propagate(n, l, r);
		seg[n].mn = min({ seg[n].mn, a * max(l,L) + b, a * min(r,R) + b });
		ll m = l + r >> 1;
		if (l < L || R < r) {
			if (L <= m) insert(L, R, a, b, seg[n].l, l, m);
			if (m + 1 <= R) insert(L, R, a, b, seg[n].r, m + 1, r);
			return;
		}
		ll& sa = seg[n].a, & sb = seg[n].b;
		if (a * l + b < sa * l + sb) swap(a, sa), swap(b, sb);
		if (a * r + b >= sa * r + sb) return;
		if (a * m + b < sa * m + sb) {
			swap(a, sa), swap(b, sb);
			insert(L, R, a, b, seg[n].l, l, m);
		}
		else insert(L, R, a, b, seg[n].r, m + 1, r);
	}
	
	ll get(ll x, int n, ll l, ll r) 
	{
		if (n == 0) return inf;
		propagate(n, l, r);
		ll ret = seg[n].a * x + seg[n].b, m = l + r >> 1;
		if (x <= m) return min(ret, get(x, seg[n].l, l, m));
		return min(ret, get(x, seg[n].r, m + 1, r));
	}
	
	ll get(ll L, ll R, int n, ll l, ll r) 
	{
		if (n == 0) return inf;
		if (r < L || R < l || L > R) return inf;
		propagate(n, l, r);
		if (L <= l && r <= R) return seg[n].mn;
		ll m = l + r >> 1;
		return min({ seg[n].a * max(l,L) + seg[n].b, seg[n].a * min(r,R) + seg[n].b, get(L, R, seg[n].l, l, m), get(L, R, seg[n].r, m + 1, r) });
	}
	
	void insert(ll L, ll R, ll a, ll b)  // [l,r] insert ax+b
	{
		insert(L, R, a, b, 1, _l, _r);
	}
	
	ll get(ll x) {
		return get(x, 1, _l, _r);
	}
	
	ll get(ll L, ll R) {
		return get(L, R, 1, _l, _r);
	}
};

int main()
{
	LiChao tree(-1e12, 1e12); // range setting

	int q; ci(q);

	while (q--)
	{
		int tp; ci(tp);		

		if (tp & 1) // insert ax+b 
		{
			LL a, b; ci(a >> b);
			tree.insert(-1e12, 1e12, -a, -b);
		}
		else // get maximum y at point x
		{
			LL x; ci(x);
			co(-tree.get(x)<<"\n");
		}
	}

	return 0;
}

