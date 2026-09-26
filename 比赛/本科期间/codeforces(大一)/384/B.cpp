#include <iostream>
#include <cstdio>
using namespace std;
long long part(long long n,long long k)
{
//	printf("%d %d\n",n,k);
	if ((1ll<<(n-1))==k) return n;
	if ((1ll<<(n-1))<k) return part(n-1,k-(1ll<<(n-1)));
	return part(n-1,k);
}
int main()
{
	long long n,k; 
    scanf("%I64d%I64d",&n,&k);
    printf("%I64d",part(n,k));
    return 0;
}
