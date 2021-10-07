vector<int> pr; // prime set
int sp[max_v]; // minimum prime
int cnt[max_v]; // 2 ^ (prime_num)
int mu[max_v];

void get_sieve() // O(n)
{ 
	cnt[1] = 1;
	for(int i = 2; i<max_v;++i)
	{
		if (!sp[i]) pr.push_back(i), cnt[i] = 2, mu[i] = -1;
		for (auto& x : pr)
		{
			if (x * i >= max_v) break;
			sp[x * i] = x;
			cnt[x * i] = i % x == 0 ? cnt[i] : cnt[i]+1;
			mu[x * i] = (i % x != 0) * (-mu[i]);
			if (i % x == 0) break;
		}
	}
};
