#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#define N 1001
using namespace std;
int n;
int dp[256][9];//表示到这个是第几位 
int b[9][N];
int a[N];
int l,r;
bool judge(int K)
{
	register int i,j,k;
	for (i=0;i<256;i++)
		for (j=0;j<=K%8+1;j++) dp[i][j]=n+1;
	dp[0][0]=0;
    for (i=0;i<255;i++)
    	for (j=0;j<=K%8;j++)
    	{
    		if (dp[i][j]>n) continue;
    		for (k=0;k<8;k++)
    		{
    			if ((i>>k)&1) continue;
	    		for (int x=0;x<2;x++)
				{
					if (b[k][n]<b[k][dp[i][j]]+K/8+x) continue;
					int p=lower_bound(b[k],b[k]+n+1,b[k][dp[i][j]]+K/8+x)-b[k];//findpos
					dp[i^(1<<k)][j+x]=min(dp[i^(1<<k)][j+x],p);//change
				}
			}
		}
	return dp[255][K%8]<=n;
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++) scanf("%d",a+i);
    int mid;
	for (int i=0;i<n;i++)//记录当前位置个数 
	{
		a[i]--;
		for (int j=0;j<8;j++)
			b[j][i+1]=b[j][i];
		b[a[i]][i+1]++;
	}
    l=0;r=n+1;
    while (r-l>1)
    {
    	mid=(l+r)/2;
    	if (judge(mid)) l=mid;
    	else r=mid;
	}
	printf("%d",l);
    return 0;
}
