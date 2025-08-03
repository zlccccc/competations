#include <iostream>
#include <cstdio>
using namespace std;
int a[101];
int b[101];
int main()
{
	int n,m,sum;
	int i;
	int l,r; 
	scanf("%d%d",&n,&m);
	sum=0;
	for (i=1;i<=n;i++) scanf("%d",a+i);
	for (i=2;i<=n;i++) a[i]+=a[i-1];
	a[0]=0; 
	for (i=0;i<m;i++)
	{
		scanf("%d%d",&l,&r);
		if (a[r]-a[l-1]>0) sum+=a[r]-a[l-1];
	}
	printf("%d",sum);
}

