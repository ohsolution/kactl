/**
 * Author: Cube219
 * Date: 2021-10-07
 * License: CC0
 * Description: Get substring of hash.
 * Time: $O(n) when init, O(1) to get$
 * Usage:
 *  HashStr hs(str); v = hs.substr(0, 10);
 */
#pragma once

template <ll h = 3137, ll m = 998244353>
struct HashStr {
	vector<ll> hv;
	vector<ll> hpow;
	HashStr(const string& str){
		int n = str.size();
		hv.resize(n);
		hpow.resize(n);
		hv[0] = str[0];
		hpow[0] = 1;
		for(int i = 1; i < n; ++i) {
			hv[i] = (hv[i - 1] * h + str[i]) % m;
			hpow[i] = (hpow[i - 1] * h) % m;
		}
	}
	// [l, r)
	ll substr(int l, int r) {
		ll res = hv[r - 1];
		if(l > 0) {
			res -= hv[l - 1] * hpow[r - l];
			res = ((res % m) + m) % m;
		}
		return res;
	}
};
