/**
 * Author: koosaga
 * 
 * Description: Half-plane Intersection \\
 * Left half-plane for vector from (x1,y1) to (x2,y2) is equal to \\
 * a=y2-y1, b=x1-x2, c=x1*y2-x2*y1 \\
 * To move L[i] parellel to original line by d \\
 * long double h=hypot(L[i].a,L[i].b); \\
 * long double dx=d*L[i].a/h, dy=d*L[i].b/h; \\
 * L[i].c-=dx*L[i].a+dy*L[i].b;  // note that -=  \\
 * HPI function returns HPI polygon \\
 */

#include<bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef long long ll;

const double eps = 1e-8;
typedef pair<long double, long double> pi;
long double ccw(pi p1, pi p2, pi p3){
    p2.fi-=p1.fi; p2.se-=p1.se;
    p3.fi-=p1.fi; p3.se-=p1.se;
    return p2.fi*p3.se - p2.se*p3.fi;
}
bool z(long double x){ return fabs(x) < eps; }
struct line{
	long double a, b, c;
	bool operator<(const line &l)const{
		bool flag1 = pi(a, b) > pi(0, 0);
		bool flag2 = pi(l.a, l.b) > pi(0, 0);
		if(flag1 != flag2) return flag1 > flag2;
		long double t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
		return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
	}
	pi slope(){ return pi(a, b); }
};
pi cross(line a, line b){
	long double det = a.a * b.b - b.a * a.b;
	return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}
bool bad(line a, line b, line c){
	if(ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
	pi crs = cross(a, b);
	return crs.first * c.a + crs.second * c.b >= c.c;
}
bool HPI(vector<line> v, vector<pi> &solution){ // ax + by <= c;
	sort(v.begin(), v.end());
	deque<line> dq;
	for(auto &i : v){
		if(!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope()))) continue;
		while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
		while(dq.size() >= 2 && bad(i, dq[0], dq[1])) dq.pop_front();
		dq.push_back(i);
	}
	while(dq.size() > 2 && bad(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
	while(dq.size() > 2 && bad(dq.back(), dq[0], dq[1])) dq.pop_front();
	vector<pi> tmp;
	for(int i=0; i<dq.size(); i++){
		line cur = dq[i], nxt = dq[(i+1)%dq.size()];
		if(ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps) return false;
		tmp.push_back(cross(cur, nxt));
	}
	solution = tmp;
	return true;
}