#include <iostream>
#include <cstdio>
using namespace std;
int a[101];
int b[101];
int main()
{
	long long m,sum;
	long long n,a,b,c;
	scanf("%I64d%I64d%I64d%I64d",&n,&a,&b,&c);
	n=4-n%4;
	n%=4;
	sum=0;
	if (b>a*2) b=a*2;
	if (c>b+a) c=b+a;
	if (a>b+c) a=b+c;
	if (a>c*3) a=c*3;
	if (b>c*2) b=c*2;
	if (n==3) sum=c;
	if (n==2) sum=b;
	if (n==1) sum=a;
	printf("%I64d",sum);
}
