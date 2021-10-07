#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#ifdef OHSOLUTION
#define ce(t) cerr<<t
#define AT cerr << "\n=================ANS=================\n"
#define AE cerr << "\n=====================================\n"
#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl;
#define __builtin_popcount __popcnt
#define __builtin_popcountll __popcnt64
const LL LNF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;
template<typename T, typename U> void ckmax(T& a, U b) { a = a < b ? b : a; }
template<typename T, typename U> void ckmin(T& a, U b) { a = a > b ? b : a; }
template<typename T, typename U> void MOD(T& a, U b) { a += b; if (a >= mod) a -= mod; };
#else
#define AT
#define AE
#define ce(t)
#endif
