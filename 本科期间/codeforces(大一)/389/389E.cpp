#include <cstdio>
int a[10000002];
int b[10000002];
int i,j;
long long n,k;
long long num;
int main()
{
	scanf("%I64d%I64d",&n,&k);
	for (i=0;i<n;i++){
		scanf("%d",&j);
		a[j]++;
	}
	for (i=10000000;i>0;i--)
	{
		num+=a[i];
		a[i/2]+=a[i]+b[i]; b[i-i/2]+=a[i]+b[i];
		if (num>=k)
		{
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
}
