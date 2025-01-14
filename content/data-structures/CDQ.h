/**
 * Author: ohsolution
 * Date: 2021-10-08
 * Description:
 */

struct Node {
	LL t, x, y, v, i, sgn;
};

vector<Node> vi;
vector<LL> ans;
LL arr[max_v];
int w;

void cdq(int l, int r) {    
	if (l +1 == r) return;

	int mid = l + r >> 1;

	cdq(l, mid); cdq(mid, r);

	vector<Node> tmp;
	vector<setl> his;

	int a = l, b = mid;

	while (a < mid && b < r) {
		if (vi[a].x <= vi[b].x) {
			upd(vi[a].y, vi[a].v); // fenwick
			his.push_back({ vi[a].y,-vi[a].v });
			tmp.push_back(vi[a++]);
		} else {
			ans[vi[b].i] += vi[b].sgn * query(vi[b].y);
			tmp.push_back(vi[b++]);
		}
	}

	while (a < mid) tmp.push_back(vi[a++]);
	while (b < r) {
		ans[vi[b].i] += vi[b].sgn * query(vi[b].y);
		tmp.push_back(vi[b++]);        
	}
	
	fa(i, l, r) vi[i] = tmp[i - l];
	for (auto& x : his) upd(x.first, x.second); // roll-back
}

int main() {
	ans.push_back(0);
  
	while (1) {
		ci(tp);

		if (tp == 3) break;

		// update point
		if (tp & 1) {
			int x, y, val; ci(x >> y >> val);
			vi.push_back({ ct,x,y,val,0,0 });
		} else {
			// count inner point in ractangle
			int lx, ly, rx, ry; ci(lx >> ly >> rx >> ry);
			vi.push_back({ ct,lx - 1,ly - 1,0,(LL)ans.size(),1 });
			vi.push_back({ ct,rx,ry ,0,(LL)ans.size(),1 });
			vi.push_back({ ct,lx - 1,ry,0,(LL)ans.size(),-1 });
			vi.push_back({ ct,rx,ly - 1,0,(LL)ans.size(),-1 }); // idx,(x,y) cod, number of add point, ans save idx,sign
			ans.push_back(0);
		}
		++ct;
	}
	
	cdq(0, vi.size());    
	fa(i, 1, ans.size()) co(ans[i] << "\n");

	return 0;
}
