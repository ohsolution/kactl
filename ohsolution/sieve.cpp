vector<int> pr; // 소수 set
int sp[max_v]; // 최소 소인수 
int cnt[max_v]; // 2 ^ 소인수 개수
int mu[max_v]; // 뫼비우스 

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
			cnt[x * i] = i % x == 0 ? cnt[i] : cnt[i]+1; // 항상 하나의 소수 x 만이 합성수 i에 곱해지므로 곱셈함수를 구하기 쉬움
			mu[x * i] = (i % x != 0) * (-mu[i]);
			if (i % x == 0) break;
		}
	}
};
