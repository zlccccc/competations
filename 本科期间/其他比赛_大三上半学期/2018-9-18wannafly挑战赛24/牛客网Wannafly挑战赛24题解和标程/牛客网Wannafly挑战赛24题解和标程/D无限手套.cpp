#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int MAXN=10000;
int a[1010],b[1010];
int p[10101];
int main()
{
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		a[i]%=mod;
		b[i]%=mod;
	}
	p[0]=1;
	for(int j=1;j<=m;j++)
	{
		int x1=(a[j]-b[j]+1+mod)%mod,x2=((a[j]+b[j])%mod+mod-2)%mod;
		for(int i=MAXN;i>=0;i--)
		{
			p[i+2]+=1ll*x1*p[i]%mod;
			p[i+2]%=mod;
			p[i+1]+=1ll*x2*p[i]%mod;
			p[i+1]%=mod;
		}
		int tt=3;
		while(tt--)
		for(int i=0;i<MAXN;i++)
		{
			p[i]+=p[i-1];
			p[i]%=mod;
		}
	}
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",p[x]);
	}
	return 0;
}
