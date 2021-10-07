/**
 * Author: Cube219
 * Date: 2021-10-07
 * License: CC0
 * Description: Finds binomial coefficient. MOD must be prime.
 * Usage:
 *  MAXN < MOD -> init(); bi_coeff(n, r)
 *  MAXN > MOD -> MAXN = MOD; init(); bi_coeff_lucas(n, r);
 * Time:
 *  MAXN < MOD -> O(N) when init, O(1) to get
 *  MAXN > MOD -> O(MOD) when init, O(logN) to get
 */
#pragma once

constexpr ll MAXN = 1000000, MOD = 1000000007;
ll fact[MAXN + 1], invfact[MAXN + 1];
ll pw(ll a, ll b) {
    ll res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void init(){
    fact[0] = 1;
    for(int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN] = pw(fact[MAXN], MOD - 2);
    for(int i = MAXN - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}
ll bi_coeff(int n, int r) {
    ll factn = fact[n];
    ll invrnr = invfact[r] * invfact[n - r] % MOD;
    return factn * invrnr % MOD;
}
ll bi_coeff_lucas(ll n, ll r) {
    ll res = 1;
    while(n > 0 || r > 0) {
        ll a = n % MOD;
        ll b = r % MOD;
        res *= bi_coeff(a, b);
        res %= MOD;
        n /= MOD; r /= MOD;
    }
    return res;
}
