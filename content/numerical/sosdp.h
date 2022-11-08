
// dp2[t][i] = sigma dp[t][subset i]

fa(t, 1, 18)
{
    fa(i, 0, 1 << 17) dp2[t][i] = dp[t][i];
    for (int j = 0; j < 17; j++) for (int i = 0; i < (1 << 17); i++) if (i & (1 << j)) MOD(dp2[t][i] , dp2[t][i ^ (1 << j)]);
}
