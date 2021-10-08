/**
 * Author: ohsolution
 * Date: 2021-10-08
 * License: CC0
 * Description: Prime sieve for generating all primes smaller than LIM.
 * Time: O(N)
 */
#pragma once

const int LIM = 1e6;
vector<int> pr; // prime set
int sp[LIM]; // minimum prime
int cnt[LIM]; // 2 ^ (prime_num)?
int mu[LIM]; // Mobius

void get_sieve()
{
	cnt[1] = 1;
	mu[1] = 1;
	for(int i = 2; i < LIM; ++i) {
		if(!sp[i]) pr.push_back(i), cnt[i] = 2, mu[i] = -1;
		for(auto& x : pr) {
			if(x * i >= LIM) break;
			sp[x * i] = x;
			cnt[x * i] = i % x == 0 ? cnt[i] : cnt[i] + 1;
			mu[x * i] = (i % x != 0) * (-mu[i]);
			if(i % x == 0) break;
		}
	}
}
