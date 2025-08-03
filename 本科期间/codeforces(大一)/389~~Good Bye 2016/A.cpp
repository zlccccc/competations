#include <cstdio>
#include <cmath>
int n,k,t;
int main()
{
	scanf("%d%d",&n,&k);
	k=240-k;
	k/=5;
	t=0;
	while ((t+2)*(t+1)/2<=k) t++;
	if (t>n) t=n;
    printf("%d",t);
}
