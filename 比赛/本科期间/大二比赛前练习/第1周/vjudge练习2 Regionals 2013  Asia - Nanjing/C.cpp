#include <cstdio>
#include <cstring>
int dp[2][1<<10][21];
char mp[101][11];
#define mod 1000000007
int main()
{
    int N,M,C,D,ans,now;
    while(scanf("%d%d%d%d",&N,&M,&C,&D)!=EOF)
    {
        for(int i=0;i<N;i++)
            scanf("%s",mp[i+1]);
        memset(dp,0,sizeof(dp));
        dp[0][(1<<M)-1][0]=1;
        now=0;
        for(int i=1;i<=N;i++)
            for(int j=0;j<M;j++)
            {
                now^=1;
                memset(dp[now],0,sizeof(dp[now]));
                if(mp[i][j]=='1')
                {
                    for(int k=0;k<=D;k++)
                    {
                        for(int l=0;l<(1<<M);l++)
                        {
                            if(k&&(l&(1<<j)))
                                dp[now][l][k]=(dp[now][l][k]+dp[now^1][l][k-1])%mod;
                            if(j&&(l&(1<<j))&&(!(l&(1<<(j-1)))))
                                dp[now][l|(1<<(j-1))][k]=(dp[now][l|(1<<(j-1))][k]+dp[now^1][l][k])%mod;
                            dp[now][l^(1<<j)][k]=(dp[now][l^(1<<j)][k]+dp[now^1][l][k])%mod;
                        }
                    }
                }
                else
                {
                    for(int k=0;k<=D;k++)
                        for(int l=0;l<(1<<M);l++)
                            if(l&(1<<j))
                                dp[now][l][k]=(dp[now][l][k]+dp[now^1][l][k])%mod;
                }
            }
        ans=0;
        for(int i=C;i<=D;i++)
            ans=(ans+dp[now][(1<<M)-1][i])%mod;
        printf("%d\n",ans);
    }
    return 0;
}
