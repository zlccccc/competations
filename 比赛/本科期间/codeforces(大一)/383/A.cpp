#include <cstdio>
#include <iostream>
using namespace std;
int gcd(int a,int b)
{
	if (a<b) return gcd(b,a);
	if (b==0) return a;
	return gcd(b,a%b);
}
int main()
{
	int n,m;
	int i,j,k;
	int ans=1;
	bool judge;
	int x;
	int a[101];
	bool b[101];
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	for (i=1;i<=n;i++) b[i]=0;
	for (i=1;i<=n;i++)
	{
		k=1;
		if (b[i]==1) continue;
		b[i]=true;
		for (j=a[i];!b[j];j=a[j],k++) b[j]=true;
		if (j!=i) {judge=1; break;}
		if (k%2==0) k/=2;
		ans=ans*k/gcd(ans,k);
	}
	if (judge) printf("-1\n");
	else printf("%d",ans);
	return 0;
}
