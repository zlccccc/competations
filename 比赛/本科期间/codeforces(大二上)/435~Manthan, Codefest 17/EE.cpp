#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;

ll len,wei[111],b,dp[11][111][2130][2];

ll dfs(ll pos,ll fff,ll gg,ll flag){
	if(pos==0){
		return (!fff)&&gg;
	}
	if(flag==0&&dp[b][pos][fff][gg]!=-1)return dp[b][pos][fff][gg];
	ll ans=0;
	ll ed=flag?wei[pos]:b-1;
	for(ll i=0;i<=ed;i++){
		ll nxtgg=((gg|i)>0);
		ll nxtfff=fff;
		if(nxtgg)nxtfff^=(1<<i);
		ans+=dfs(pos-1,nxtfff,nxtgg,flag&&i==ed);
	}
	if(!flag)dp[b][pos][fff][gg]=ans;
	printf("%d,%d,%d,%d,%d\n",pos,fff,gg,flag,ans);
	return ans;
}

ll solve(ll x){
	len=0;
	while(x){
		wei[++len]=x%b;
		x/=b;
	}
	ll ans=dfs(len,0,0,1);
	return ans;
}

int main()
{
	ll t,l,r;
	scanf("%I64d",&t);
	memset(dp,-1,sizeof(dp));
	while(t--){
		scanf("%I64d%I64d%I64d",&b,&l,&r);
		printf("%d,%d\n",solve(r),solve(l-1));
//		printf("%I64d\n",solve(r)-solve(l-1));
	}
	return 0;
}
