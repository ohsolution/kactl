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

template <ll h1 = 3137, ll m1 = 998244353, ll h2 = 53, ll m2 = 1610612741>
struct StrHash {
	vector<ll> hv, hpow;
	vector<ll> hv2, hpow2;

	void build(const string& str) {
		int n = str.size();
		hv.resize(n);
		hpow.resize(n);

		hv[0] = str[0];
		hpow[0] = 1;
		for(int i = 1; i < n; ++i) {
			hv[i] = (hv[i - 1] * h1 + str[i]) % m1;
			hpow[i] = (hpow[i - 1] * h1) % m1;
		}

		hv2.resize(n);
		hpow2.resize(n);

		hv2[0] = str[0];
		hpow2[0] = 1;
		for(int i = 1; i < n; ++i) {
			hv2[i] = (hv2[i - 1] * h2 + str[i]) % m2;
			hpow2[i] = (hpow2[i - 1] * h2) % m2;
		}
	}

	// [l, r]
	ll substr(int l, int r) {
		ll res = hv[r-1];
		if(l > 0) {
			res -= hv[l - 1] * hpow[r - l];
			res = ((res % m1) + m1) % m1;
		}
		ll res2 = hv2[r-1];
		if(l > 0) {
			res2 -= hv2[l - 1] * hpow2[r - l];
			res2 = ((res2 % m2) + m2) % m2;
		}
		return (res << 32) | res2;
	}
};
