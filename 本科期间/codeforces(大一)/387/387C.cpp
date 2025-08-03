#include <cstdio>
int n,q;
int i,j,k;
int a[100001];
int b[101]={0};
int main()
{
	scanf("%d%d",&n,&q);
	int ti,ki,di,tt;
	int sum;
	scanf("%d",&ti);
	for (i=0;i<q;i++)
	{
		scanf("%d%d",&ki,&di);
		k=0;
		for (j=0;j<n;j++)
			if (b[j]==0) k++;
//			printf("%d ",k);
		if (k<ki) {
			printf("-1\n");
		}
		else 
		{
			sum=0;
			for (j=0;ki;j++)
				if (b[j]==0)
				{
					sum+=j+1;
					b[j]=di;
					ki--;
				}
			printf("%d\n",sum);
		}
		if (i!=q-1) scanf("%d",&tt);
//		printf("    %d  ",tt-ti);
		for (j=0;j<n;j++)
		{
			if (b[j]!=0) b[j]-=tt-ti;
			if (b[j]<0) b[j]=0;
		}
		ti=tt;
	}
}
