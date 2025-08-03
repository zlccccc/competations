#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int n,q,m;
int w;
int i,j,k;
int t;
int a[200001];
int main()
{
	scanf("%d%d",&n,&k);
	w=0;m=0;
	for (i=0;i<n;i++)
	{
		scanf("%d",&t);
		if (t>=0) w++;
		else {
		a[m++]=w;
		w=0;
		}
	}
	if (m>k) {
		printf("-1");
		return 0;
	}
	if (m==0) {
		printf("0");
		return 0;
	}
	sort(a+1,a+m);
	j=m*2;
	k=k-m;
//	printf("%d  ",k);
	for (i=1;i<m;i++)
	{
		if (k-a[i]>=0)
		{
			k-=a[i];
			j-=2;
		}
		else break;
	}
//	printf("%d %d ",k,w);
	if (k>=w) j--;
	printf("%d",j);
}
