/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^2)
 */

int n, m[5005], sum[5005];
int dp[5005][5005], pos[5005][5005];
const int INF=1e9;

int main()
{
    scanf("%d",&n);
    for(int i=1 ; i<=n ; i++){
        scanf("%d",&m[i]);
        pos[i][i]=i;
        sum[i]=sum[i-1]+m[i];
    }
    //calculate DP diagonally
    for(int len=2 ; len<=n ; len++){
        for(int i=1 ; i<=n-len+1 ; i++){
            dp[i][i+len-1]=INF;
            int s=pos[i][i+len-2], f=pos[i+1][i+len-1];
            for(int j=s ; j<=f ; j++){
                if(j<n && dp[i][i+len-1]>dp[i][j]+dp[j+1][i+len-1]){
                    pos[i][i+len-1]=j;
                    dp[i][i+len-1]=dp[i][j]+dp[j+1][i+len-1];
                }
            }
            dp[i][i+len-1]+=sum[i+len-1]-sum[i-1];
        }
    }
    printf("%d\n",dp[1][n]);
    return 0;
}