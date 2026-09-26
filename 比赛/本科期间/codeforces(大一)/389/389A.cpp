#include <cstdio>
long long n,m,k,t;
int main()
{
	scanf("%I64d%I64d%I64d",&n,&m,&k);
	t=(k-1)/(2*m)+1;
	printf("%I64d %I64d",t,(k-(t-1)*m*2-1)/2+1);
	if (k%2==1) printf(" L");
	else printf(" R");
}
