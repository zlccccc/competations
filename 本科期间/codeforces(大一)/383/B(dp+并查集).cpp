#include <cstdio>
#include <iostream>
#define DEBU
using namespace std;
int w[1001];
int b[1001];
int v[1001];//dp
int u[1001];//辅助 
int f[1001];//并查集
int getfather(int s)
{
	if (f[s]==s) return s;
	f[s]=getfather(f[s]);
	return f[s];
}
int main()
{
	int n,m,w0;
	int i,j,k;
	int xi,yi;
	int w1,b1;//重量和 
	scanf("%d%d%d",&n,&m,&w0);
	for (i=1;i<=n;i++) scanf("%d",&w[i]);
	for (i=1;i<=n;i++) scanf("%d",&b[i]);
	for (i=1;i<=n;i++) f[i]=i;
	for (i=1;i<=m;i++)
	{
		scanf("%d%d",&xi,&yi);
		f[getfather(xi)]=getfather(yi);
	}
	for (i=1;i<=n;i++) f[i]=getfather(i);
#ifdef DEBUG
		for (k=0;k<=n;k++) printf("%d ",f[k]);
		printf("\n");
		for (k=0;k<=n;k++) printf("%d ",w[k]);
		printf("\n");
		for (k=0;k<=n;k++) printf("%d ",b[k]);
		printf("\n");
		printf("\n");
#endif
	for (i=1;i<=n;i++)
		for (j=i;j<=n;j++)
		if (f[i]>f[j])//将一块的放一起 
		{
			f[i]^=f[j]^=f[i]^=f[j];
			w[i]^=w[j]^=w[i]^=w[j];
			b[i]^=b[j]^=b[i]^=b[j];
		}
#ifdef DEBUG
		for (k=0;k<=n;k++) printf("%d ",f[k]);
		printf("\n");
		for (k=0;k<=n;k++) printf("%d ",w[k]);
		printf("\n");
		for (k=0;k<=n;k++) printf("%d ",b[k]);
		printf("\n");
#endif
	for (i=0;i<=n;i++) v[i]=0;
	for (i=1;i<=n;)
	{
		for (k=0;k<=w0;k++) u[k]=v[k];
		w1=0; b1=0;
		for (j=i;f[j]==f[i];j++)
		{
			w1+=w[j]; b1+=b[j];
			for (k=w[j];k<=w0;k++)
			{
				if (k>0) u[k]=max(u[k-1],u[k]);
				if (k-w[j]>=0) u[k]=max(u[k],v[k-w[j]]+b[j]);
			}
		}
		for (k=w1;k<=w0;k++)
		{
			if (k>0) u[k]=max(u[k-1],u[k]);
			if (k-w1>=0) u[k]=max(u[k],v[k-w1]+b1);
		}
		i=j;
		for (k=0;k<=w0;k++) v[k]=u[k];
#ifdef DEBUG
		for (k=0;k<=w0;k++) printf("%d ",v[k]);
		printf("\n");
#endif
	}
	printf("%d",v[w0]);
	return 0;
}
