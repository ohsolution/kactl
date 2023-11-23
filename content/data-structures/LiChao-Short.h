/**
 * Author: ansol4328
 * Date: 2023-11-23
 * Description:
*/
const ll yINF = 1e18;
const ll xINF = 1e12;

struct L {
	ll a, b;
	L(ll a = 0, ll b = -yINF) : a(a), b(b) {}
	ll val(ll x) { return a * x + b; }
};

struct node {
	L e;
	ll st, fn;
	node *lc, *rc;
	node(ll st, ll fn) : st(st), fn(fn), lc(nullptr), rc(nullptr) {}
	void push(L q) {
		ll mid = (st + fn) >> 1;
		bool b = e.val(mid) < q.val(mid);
		if (b) swap(e, q);
		bool a = e.val(st) < q.val(st);
		bool c = e.val(fn) < q.val(fn);
		if (a == c) return;
		if (a) {
			if (!lc) lc = new node(st, mid);
			lc->push(q);
		}
		if (c) {
			if (!rc) rc = new node(mid + 1, fn);
			rc->push(q);
		}
	}
	ll qry(ll x) {
		ll ret = e.val(x);
		ll mid = (st + fn) >> 1;
		if (x <= mid && lc) ret = max(ret, lc->qry(x));
		if (x > mid && rc) ret = max(ret, rc->qry(x));
		return ret;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(false);
	node* root = new node(-xINF, xINF);
	int q;
	for (cin >> q; q; q--) {
		int t; cin >> t;
		if (t == 1) {
			ll a, b;
			cin >> a >> b;
			root->push({ a, b });
		}
		else {
			ll x;
			cin >> x;
			cout << root->qry(x) << '\n';
		}
	}
	return 0;
}