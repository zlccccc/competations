#include <cstdio>
#include <iostream>
using namespace std;
int main()
{
	int n,m;
	int i,j,k;
	long long ans=0;
	int x;
	int a[200001];
	int b[200001];
	scanf("%d%d",&n,&x);
	for (i=0;i<200001;i++) b[i]=0;
	for (i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]]++;
	}
	if (x==0) {for (i=0;i<n;i++) if (b[a[i]]>0) ans+=b[a[i]]-1;}
	else for (i=0;i<n;i++) ans+=b[x^a[i]];
//	printf("%d",b[100000]);
//	if (b[a[i]]*b[x^a[i]]!=0) printf("\n%d %d  %d",a[i],x^a[i],b[a[i]]*b[x^a[i]]);}
	printf("%I64d",ans/2);
	return 0;
}
