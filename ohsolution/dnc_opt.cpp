function<void(int, int, int, int, int)> dnc = [&](int lev, int l, int r, int s, int e)
{
  if (l > r || s > e) return;

  int mid = l + r >> 1;
  int opt = -1;
  dp[lev][mid] = LNF;  

  fa(i, s, min(mid,e) + 1)
  {
    LL t = dp[lev - 1][i] + cost(i + 1, mid);

    if (dp[lev][mid] > t)
    {
      dp[lev][mid] = t;
      opt = i;
    }
  }

  dnc(lev, l, mid - 1, s, opt);
  dnc(lev, mid + 1, r, opt, e);
};

function<void(int, int, int, int)> dnc = [&](int l, int r, int s, int e)
{
	if (l > r ||s > e) return;

	int mid = l + r >> 1;
	int opt = -1;
	LL maxi = -LNF;

	fa(i, s, e+1)
	{
		LL dx = b[i].first - a[mid].first;
		LL dy = b[i].second - a[mid].second;

		LL ret = (dx < 0 && dy < 0) ? 0 : dx * dy;

		if (ret > maxi)
		{
			maxi = ret;
			opt = i;
		}
	}

	ckmax(ans, maxi);

	dnc(l, mid - 1, s, opt+1); dnc(mid + 1, r, opt-1, e);
};
