#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int a[302];
int b[302][302];
int c[302][302];
int bracket1[302];
int bracket2[302];
void out(int l,int r)
{
	if (r-l<=1) return;
	bracket1[l]++;
	bracket2[r]++;
	int k=c[l][r];
	out(l,k);
	out(k,r);
}
int main()
{
	int n;
	int i,j,k,t;
	while (~scanf("%d",&n))
	{
		for (i=0;i<n+1;i++) scanf("%d",a+i);
		for (i=0;i<=n;i++)
			for (j=i;j<=n;j++) b[i][j]=c[i][j]=0;
		for (t=2;t<=n;t++)
			for (i=0;i<=n-t;i++)
				{
					j=i+t;
					for (k=i+1;k<j;k++)
					if (c[i][j]==0||b[i][j]>=b[i][k]+b[k][j]+a[i]*a[j]*a[k])
					{
						c[i][j]=k;
						b[i][j]=b[i][k]+b[k][j]+a[i]*a[j]*a[k];
					}
				}
		for (i=0;i<=n;i++) bracket1[i]=bracket2[i]=0;
		out(0,n);
		printf("%d\n",b[0][n]);
		for (i=0;i<n;i++)
		{
			for (j=0;j<bracket2[i];j++) printf(")");
			for (j=0;j<bracket1[i];j++) printf("(");
			printf("A%d",i+1);
		}
		for (j=0;j<bracket2[n];j++) printf(")");
		printf("\n");
	}
}
